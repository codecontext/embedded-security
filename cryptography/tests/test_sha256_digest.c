#include "sha256_digest.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

static int check_digest(const char *label,
                        const uint8_t *input,
                        size_t input_length,
                        const uint8_t expected[SHA256_DIGEST_SIZE])
{
    uint8_t output[SHA256_DIGEST_SIZE];

    if (sha256_digest(input,
                      input_length,
                      output,
                      sizeof(output)) != SHA256_OK) {
        fprintf(stderr, "%s: digest operation failed\n", label);
        return 1;
    }

    if (memcmp(output, expected, SHA256_DIGEST_SIZE) != 0) {
        fprintf(stderr, "%s: digest did not match the known answer\n", label);
        return 1;
    }

    return 0;
}

int main(void)
{
    static const uint8_t empty_digest[SHA256_DIGEST_SIZE] = {
        0xe3, 0xb0, 0xc4, 0x42, 0x98, 0xfc, 0x1c, 0x14,
        0x9a, 0xfb, 0xf4, 0xc8, 0x99, 0x6f, 0xb9, 0x24,
        0x27, 0xae, 0x41, 0xe4, 0x64, 0x9b, 0x93, 0x4c,
        0xa4, 0x95, 0x99, 0x1b, 0x78, 0x52, 0xb8, 0x55
    };
    static const uint8_t abc_digest[SHA256_DIGEST_SIZE] = {
        0xba, 0x78, 0x16, 0xbf, 0x8f, 0x01, 0xcf, 0xea,
        0x41, 0x41, 0x40, 0xde, 0x5d, 0xae, 0x22, 0x23,
        0xb0, 0x03, 0x61, 0xa3, 0x96, 0x17, 0x7a, 0x9c,
        0xb4, 0x10, 0xff, 0x61, 0xf2, 0x00, 0x15, 0xad
    };
    uint8_t output[SHA256_DIGEST_SIZE];
    uint8_t short_output[SHA256_DIGEST_SIZE - 1U];
    int failures = 0;

    failures += check_digest("empty", NULL, 0U, empty_digest);
    failures += check_digest("abc",
                             (const uint8_t *)"abc",
                             3U,
                             abc_digest);

    memset(output, 0xA5, sizeof(output));
    memset(short_output, 0xA5, sizeof(short_output));
    if (sha256_digest((const uint8_t *)"abc",
                      3U,
                      short_output,
                      sizeof(short_output)) != SHA256_OUTPUT_TOO_SMALL) {
        fprintf(stderr, "short-output: expected OUTPUT_TOO_SMALL\n");
        ++failures;
    }

    for (size_t i = 0U; i < sizeof(short_output); ++i) {
        if (short_output[i] != 0xA5) {
            fprintf(stderr, "short-output: buffer changed on failure\n");
            ++failures;
            break;
        }
    }

    if (sha256_digest(NULL, 1U, output, sizeof(output)) !=
            SHA256_INVALID_ARGUMENT) {
        fprintf(stderr, "null-input: expected INVALID_ARGUMENT\n");
        ++failures;
    }

    if (sha256_digest((const uint8_t *)"abc", 3U, NULL, 0U) !=
            SHA256_INVALID_ARGUMENT) {
        fprintf(stderr, "null-output: expected INVALID_ARGUMENT\n");
        ++failures;
    }

    if (failures != 0) {
        fprintf(stderr, "%d SHA-256 test(s) failed\n", failures);
        return 1;
    }

    puts("SHA-256 tests passed");
    return 0;
}
