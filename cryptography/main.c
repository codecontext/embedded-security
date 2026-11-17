#include "xor_cipher.h"
#include "caesar_cipher.h"
#include "sha256_digest.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

static int run_xor_cipher_demo(void)
{
    const char plaintext[] = "hello, world";
    const char key[] = "key";
    uint8_t encrypted[sizeof(plaintext)] = {0};
    uint8_t decrypted[sizeof(plaintext)] = {0};
    xor_result_t result;

    // Encrypt the example message with the key.
    result = xor_encrypt(encrypted,
                         sizeof(encrypted),
                         (const uint8_t *)plaintext,
                         strlen(plaintext),
                         (const uint8_t *)key,
                         strlen(key));

    if (result != XOR_OK) {
        fputs("Could not encrypt the example message.\n", stderr);
        return 1;
    }

    // Decrypt the message with the same key.
    result = xor_encrypt(decrypted,
                         sizeof(decrypted),
                         encrypted,
                         strlen(plaintext),
                         (const uint8_t *)key,
                         strlen(key));

    if (result != XOR_OK) {
        fputs("Could not decrypt the example message.\n", stderr);
        return 1;
    }

    printf("Plaintext: %s\n", plaintext);
    printf("Recovered: %s\n", (const char *)decrypted);
    return 0;
}

static int run_caesar_cipher_demo(void)
{
    char message[] = "Hello, World!";
    caesar_result_t result =
        caesar_rotate(message, sizeof(message), 3);

    if (result != CAESAR_OK) {
        fputs("Could not rotate the message.\n", stderr);
        return 1;
    }

    printf("Rotated: %s\n", message);
    return 0;
}

static int run_sha256_demo(void)
{
    const uint8_t message[] = "abc";
    uint8_t digest[SHA256_DIGEST_SIZE];
    sha256_result_t result =
        sha256_digest(message, sizeof(message) - 1U, digest, sizeof(digest));
    size_t i;

    if (result != SHA256_OK) {
        fputs("Could not compute the SHA-256 digest.\n", stderr);
        return 1;
    }

    printf("SHA-256: ");
    for (i = 0U; i < sizeof(digest); ++i) {
        printf("%02x", (unsigned int)digest[i]);
    }
    putchar('\n');
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc == 1 || strcmp(argv[1], "xor") == 0) {
        return run_xor_cipher_demo();
    }

    if (argc == 2 && strcmp(argv[1], "caesar") == 0) {
        return run_caesar_cipher_demo();
    }

    if (argc == 2 && strcmp(argv[1], "sha256") == 0) {
        return run_sha256_demo();
    }

    fputs("Usage: cryptography_demo [xor|caesar|sha256]\n", stderr);
    return 2;
}
