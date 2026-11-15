/**
 * @file xor_cipher.c
 * @brief Educational XOR stream transform using a repeating keystream.
 *
 * @details
 * This helper demonstrates a simple symmetric transform. For each byte index
 * i, it XORs the input byte with the repeating key byte:
 *
 * @code
 * output[i] = input[i] XOR key[i % key_length]
 * @endcode
 *
 * XOR is self-inverse, so applying the same operation again with the same key
 * restores the original plaintext. The function validates the arguments and
 * output capacity before writing any transformed bytes.
 *
 * This example is educational only. It is not a production cipher and should
 * not be used as a cryptographic primitive for real security decisions.
 */
#include "xor_cipher.h"

xor_result_t xor_encrypt(uint8_t *output,
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
