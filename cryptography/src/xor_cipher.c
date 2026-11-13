/**
 * @file xor_cipher.c
 * @brief Educational XOR stream transform using a repeating keystream.
 *
 * @details
 * This helper demonstrates the simplest possible symmetric transform. For each
 * byte position i, the function takes the input byte and XORs it with the
 * matching key byte:
 * 
 * output[i] = input[i] XOR key[i % key_length].
 * 
 * Because XOR is self-inverse, applying the same operation again with the same key
 * restores the original plaintext.
 *
 * The function first validates all required arguments and checks that the output
 * buffer is large enough to hold the transformed data. Only after those checks
 * pass does it write the transformed bytes. This keeps the lesson easy to audit
 * and makes the failure mode explicit instead of silent.
 *
 * This example is educational only. It is not a production cipher and should
 * not be used as a cryptographic primitive for real security decisions.
 */
#include "xor_cipher.h"

xor_result_t xor_encrypt(
    uint8_t *output,
    size_t output_size,
    const uint8_t *input,
    size_t input_length,
    const uint8_t *key,
    size_t key_length)
{
    size_t i;

    if (output == NULL || input == NULL || key == NULL) {
        return XOR_INVALID_ARGUMENT;
    }

    if (input_length > 0U && output_size < input_length) {
        return XOR_BUFFER_TOO_SMALL;
    }

    if (key_length == 0U) {
        return XOR_INVALID_ARGUMENT;
    }

    // Perform the XOR transform with a repeating key.
    for (i = 0U; i < input_length; ++i) {
        output[i] = input[i] ^ key[i % key_length];
    }

    return XOR_OK;
}
