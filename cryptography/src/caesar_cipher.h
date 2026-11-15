#ifndef CAESAR_CIPHER_H
#define CAESAR_CIPHER_H

#include <stddef.h>

/**
 * @brief Status codes returned by the Caesar rotation helper.
 */
typedef enum caesar_result {
    /** The rotation completed successfully. */
    CAESAR_OK,
    /** A required pointer was null or the buffer length was zero. */
    CAESAR_INVALID_ARGUMENT,
    /** The destination buffer was too small to hold the rotated text. */
    CAESAR_BUFFER_TOO_SMALL
} caesar_result_t;

/**
 * @brief Rotate alphabetic characters in a buffer by a fixed shift.
 *
 * @param[in,out] text NUL-terminated buffer to transform in place.
 * @param[in] text_size Number of bytes available in text.
 * @param[in] shift Number of positions to rotate each letter. Values are
 * normalized modulo 26 to keep the mapping simple and predictable.
 * @return CAESAR_OK when the buffer is transformed; otherwise a failure code.
 */
caesar_result_t caesar_rotate(
    char *text,
    size_t text_size,
    int shift);

#endif
