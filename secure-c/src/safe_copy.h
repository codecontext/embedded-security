#ifndef SAFE_COPY_H
#define SAFE_COPY_H

#include <stddef.h>

/**
 * @brief Result codes returned by the bounded string-copy helper.
 */
typedef enum safe_copy_result {
    /** The source string was copied successfully. */
    SAFE_COPY_OK,
    /** At least one pointer was null, or the destination size was zero. */
    SAFE_COPY_INVALID_ARGUMENT,
    /** The source string did not fit within the destination buffer. */
    SAFE_COPY_BUFFER_TOO_SMALL
} safe_copy_result_t;

/**
 * @brief Copy a NUL-terminated source string into a bounded destination.
 *
 * @param[out] destination Writable buffer that receives the copied bytes.
 * @param[in] destination_size Number of bytes available in destination.
 * @param[in] source Readable, NUL-terminated source string.
 * @return SAFE_COPY_OK when the copy fits; otherwise a failure code.
 * @note The destination remains unchanged when the copy does not fit.
 */
safe_copy_result_t safe_copy(
    char *destination,
    size_t destination_size,
    const char *source);

#endif
