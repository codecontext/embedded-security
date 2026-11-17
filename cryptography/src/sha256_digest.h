#ifndef SHA256_DIGEST_H
#define SHA256_DIGEST_H

#include <stddef.h>
#include <stdint.h>

#define SHA256_DIGEST_SIZE 32U

/**
 * @brief Result codes returned by the SHA-256 helper.
 */
typedef enum sha256_result {
    /** The digest was computed successfully. */
    SHA256_OK,
    /** A required pointer was null for the supplied length. */
    SHA256_INVALID_ARGUMENT,
    /** The output buffer cannot hold the full digest. */
    SHA256_OUTPUT_TOO_SMALL,
    /** OpenSSL reported a digest operation failure. */
    SHA256_FAILURE
} sha256_result_t;

/**
 * @brief Compute a SHA-256 digest using OpenSSL's EVP API.
 * @param[in] input Bytes to hash; may be null only when input_length is zero.
 * @param[in] input_length Number of bytes to hash.
 * @param[out] output Receives exactly SHA256_DIGEST_SIZE bytes on success.
 * @param[in] output_size Capacity of the output buffer.
 * @return A status from sha256_result_t.
 * @note The output remains unchanged if the operation fails.
 */
sha256_result_t sha256_digest(const uint8_t *input,
                              size_t input_length,
                              uint8_t *output,
                              size_t output_size);

#endif
