#ifndef SAFE_INTEGER_H
#define SAFE_INTEGER_H

#include <stdint.h>

/**
 * @brief Result codes returned by the decimal integer parser.
 */
typedef enum safe_integer_parse_result {
    /** The input was parsed successfully. */
    SAFE_INTEGER_PARSE_OK,
    /** An argument was null. */
    SAFE_INTEGER_PARSE_INVALID_ARGUMENT,
    /** The input was not a signed decimal integer. */
    SAFE_INTEGER_PARSE_INVALID_FORMAT,
    /** The numeric value does not fit in int32_t. */
    SAFE_INTEGER_PARSE_OUT_OF_RANGE
} safe_integer_parse_result_t;

/**
 * @brief Parse signed decimal text into int32_t.
 * @param[in] text Readable, NUL-terminated input string.
 * @param[out] value Receives the parsed value on success; otherwise unchanged.
 * @return A status from safe_integer_parse_result_t.
 * @note Bound untrusted input and ensure it is NUL-terminated before calling.
 */
safe_integer_parse_result_t parse_int32_decimal(
    const char *text,
    int32_t *value);

#endif
