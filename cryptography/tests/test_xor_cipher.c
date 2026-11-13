#include "xor_cipher.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

static int check_case(
    const char *label,
    const char *plain,
    const char *key,
    const uint8_t *expected,
    size_t expected_length)
{
    uint8_t buffer[64] = {0};
    size_t length = strlen(plain);
    size_t i;

    if (xor_encrypt(
            buffer,
            sizeof(buffer),
            (const uint8_t *)plain,
            length,
            (const uint8_t *)key,
            strlen(key)) != XOR_OK) {
        fprintf(stderr, "%s: encrypt failed\n", label);
        return 1;
    }

    if (memcmp(buffer, expected, expected_length) != 0) {
        fprintf(stderr, "%s: ciphertext mismatch\n", label);
        return 1;
    }

    for (i = 0U; i < length; ++i) {
        buffer[i] = buffer[i] ^ ((const uint8_t *)key)[i % strlen(key)];
    }

    if (memcmp(buffer, plain, length) != 0) {
        fprintf(stderr, "%s: round-trip mismatch\n", label);
        return 1;
    }

    return 0;
}

int main(void)
{
    const char *plaintext = "HELLO";
    const char *key = "KEY";
    const uint8_t expected[] = {0x03, 0x00, 0x15, 0x07, 0x0A};
    uint8_t buffer[8] = {0};
    int failures = 0;

    failures += check_case(
        "xor-basic",
        plaintext,
        key,
        expected,
        sizeof(expected) / sizeof(expected[0]));

    if (xor_encrypt(
            buffer,
            sizeof(buffer),
            (const uint8_t *)"ABC",
            3U,
            NULL,
            3U) != XOR_INVALID_ARGUMENT) {
        fprintf(stderr, "null-key: expected INVALID_ARGUMENT\n");
        ++failures;
    }

    if (xor_encrypt(
            NULL,
            sizeof(buffer),
            (const uint8_t *)"ABC",
            3U,
            (const uint8_t *)"K",
            1U) != XOR_INVALID_ARGUMENT) {
        fprintf(stderr, "null-output: expected INVALID_ARGUMENT\n");
        ++failures;
    }

    if (xor_encrypt(
            buffer,
            2U,
            (const uint8_t *)"ABC",
            3U,
            (const uint8_t *)"K",
            1U) != XOR_BUFFER_TOO_SMALL) {
        fprintf(stderr, "short-output: expected BUFFER_TOO_SMALL\n");
        ++failures;
    }

    if (failures != 0) {
        fprintf(stderr, "%d xor_cipher test(s) failed\n", failures);
        return 1;
    }

    puts("xor_cipher tests passed");
    return 0;
}
