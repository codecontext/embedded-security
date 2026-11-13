#ifndef XOR_CIPHER_H
#define XOR_CIPHER_H

#include <stddef.h>
#include <stdint.h>

/**
 * @brief Result codes returned by the educational XOR helper.
 */
typedef enum xor_result {
    /** The transform completed successfully. */
    XOR_OK,
    /** A required pointer was null or a size was zero for a nonempty input. */
    XOR_INVALID_ARGUMENT,
    /** The caller supplied an output buffer that is too small. */
    XOR_BUFFER_TOO_SMALL
} xor_result_t;

/**
 * @brief Encrypt or decrypt a byte sequence with a repeating XOR keystream.
 *
 * @param[out] output Receives the transformed bytes.
 * @param[in] output_size Number of bytes available in output.
 * @param[in] input Source bytes to transform.
 * @param[in] input_length Number of bytes in input.
 * @param[in] key Repeating keystream bytes.
 * @param[in] key_length Number of bytes in key.
 * @return XOR_OK on success; otherwise a failure code.
 * @note XOR with the same keystream is its own inverse, so this helper can be
 * used for both encryption and decryption.
 */
xor_result_t xor_encrypt(
    uint8_t *output,
    size_t output_size,
    const uint8_t *input,
    size_t input_length,
    const uint8_t *key,
    size_t key_length);

#endif
