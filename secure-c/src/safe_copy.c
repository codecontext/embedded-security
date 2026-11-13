/**
 * @file safe_copy.c
 * @brief Bounded string copying for fixed-size destination buffers.
 *
 * @details
 * This helper keeps a defensive check before any bytes are written. The source
 * length is computed with strlen() and the NUL terminator is counted as part of
 * the required space. If the buffer is too small, the function returns
 * SAFE_COPY_BUFFER_TOO_SMALL and leaves the destination untouched. The copy is a
 * single memcpy() only after all validation passes, so the API is simple but
 * still matches the pattern used in secure C: validate early, write last.
 */
#include "safe_copy.h"

#include <string.h>

safe_copy_result_t safe_copy(
    char *destination,
    size_t destination_size,
    const char *source)
{
    size_t source_length;

    if (destination == NULL || source == NULL || destination_size == 0U) {
        return SAFE_COPY_INVALID_ARGUMENT;
    }

    source_length = strlen(source) + 1U;

    if (source_length > destination_size) {
        return SAFE_COPY_BUFFER_TOO_SMALL;
    }

    memcpy(destination, source, source_length);
    return SAFE_COPY_OK;
}
