/**
 * @file sha256_digest.c
 * @brief SHA-256 message digest through OpenSSL's high-level EVP interface.
 *
 * @details
 * SHA-256 is a cryptographic hash, not encryption. It maps any byte sequence
 * to a fixed 256-bit (32-byte) digest. It uses no secret key, and the digest is
 * not a reversible encoding: it is intended to be infeasible to recover the
 * message from its digest. The same message always gives the same digest, while
 * a small message change should give a very different digest.
 *
 * Internally, SHA-256 divides the padded message into 512-bit blocks. Padding
 * appends a 1 bit, enough 0 bits to leave room for a 64-bit message-length
 * field, then that length. Each block expands into 64 words and updates an
 * eight-word (256-bit) state through 64 rounds of fixed bit operations,
 * additions, and mixing functions. After the last block, the state is the
 * digest. OpenSSL performs these details; this wrapper uses its EVP interface.
 *
 * @code
 * message -> pad and split into 512-bit blocks
 *                    |
 *                    v
 *       initialize 256-bit SHA-256 state
 *                    |
 *                    v
 *     expand each block and run 64 rounds
 *                    |
 *                    v
 *          finalize to 32-byte digest
 * @endcode
 *
 * EVP follows the same flow through init, update, and final calls. Update may
 * be called repeatedly to process large messages without buffering the whole
 * message in this wrapper. The digest is first written to a temporary buffer;
 * it is copied to caller memory only if every EVP call succeeds and OpenSSL
 * reports the expected digest length. Thus errors leave caller output intact.
 *
 * A digest is useful as a fingerprint or for checking a downloaded file: hash
 * the received bytes and compare the result with an expected digest obtained
 * from a trusted source. If an attacker can replace both the data and expected
 * digest, this check proves nothing about who supplied them. A plain hash does
 * not encrypt or authenticate data. Use a standard authenticated construction
 * such as HMAC or a digital signature when authenticity is required; compare
 * secret-dependent authentication values with a constant-time API. This
 * educational wrapper computes a digest only and does not implement a protocol.
 */
#include "sha256_digest.h"

#include <openssl/evp.h>
#include <string.h>

sha256_result_t sha256_digest(const uint8_t *input,
                              size_t input_length,
                              uint8_t *output,
                              size_t output_size)
{
    EVP_MD_CTX *context;
    uint8_t digest[SHA256_DIGEST_SIZE];
    unsigned int digest_length = 0U;
    sha256_result_t result = SHA256_FAILURE;

    if (output == NULL || (input == NULL && input_length > 0U)) {
        return SHA256_INVALID_ARGUMENT;
    }

    if (output_size < SHA256_DIGEST_SIZE) {
        return SHA256_OUTPUT_TOO_SMALL;
    }

    context = EVP_MD_CTX_new();
    if (context == NULL) {
        return SHA256_FAILURE;
    }

    if (EVP_DigestInit_ex(context, EVP_sha256(), NULL) != 1) {
        goto cleanup;
    }

    if (input_length > 0U &&
        EVP_DigestUpdate(context, input, input_length) != 1) {
        goto cleanup;
    }

    if (EVP_DigestFinal_ex(context, digest, &digest_length) != 1 ||
        digest_length != SHA256_DIGEST_SIZE) {
        goto cleanup;
    }

    memcpy(output, digest, SHA256_DIGEST_SIZE);
    result = SHA256_OK;

cleanup:
    EVP_MD_CTX_free(context);
    return result;
}
