#include "xor_cipher.h"

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

    result = xor_encrypt(
        encrypted,
        sizeof(encrypted),
        (const uint8_t *)plaintext,
        strlen(plaintext),
        (const uint8_t *)key,
        strlen(key));

    if (result != XOR_OK) {
        fputs("Could not encrypt the example message.\n", stderr);
        return 1;
    }

    result = xor_encrypt(
        decrypted,
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

int main(void)
{
    return run_xor_cipher_demo();
}
