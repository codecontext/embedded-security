/**
 * @file safe_integer.c
 * @brief Strict, range-checked decimal parsing for signed 32-bit integers.
 *
 * @details
 * Parsing has two passes. First, a lexical scan requires an optional sign
 * followed by ASCII digits only; this rejects whitespace and suffixes that
 * strtoimax would otherwise accept or partially consume. Second,
 * strtoimax converts in base 10. Its ERANGE status and the int32_t limits are
 * checked before the result is narrowed. The output assignment is the final
 * step, so every error leaves caller state unchanged.
 *
 * The work is O(n) in input length with O(1) auxiliary storage. Because both
 * passes scan the string, callers must bound untrusted input before parsing.
 * This educational example does not validate pointer accessibility or prove
 * that a supplied buffer is NUL-terminated.
 */
#include "safe_integer.h"

#include <errno.h>
#include <inttypes.h>
#include <stdlib.h>

safe_integer_parse_result_t parse_int32_decimal(
    const char *text,
    int32_t *value)
{
    const char *digit = text;
    char *end = NULL;
    intmax_t parsed;

    if (text == NULL || value == NULL) {
        return SAFE_INTEGER_PARSE_INVALID_ARGUMENT;
    }

    if (*digit == '+' || *digit == '-') {
        ++digit;
    }

    if (*digit == '\0') {
        return SAFE_INTEGER_PARSE_INVALID_FORMAT;
    }

    for (; *digit != '\0'; ++digit) {
        if (*digit < '0' || *digit > '9') {
            return SAFE_INTEGER_PARSE_INVALID_FORMAT;
        }
    }

    errno = 0;
    parsed = strtoimax(text, &end, 10);

    if (errno == ERANGE || parsed < INT32_MIN || parsed > INT32_MAX) {
        return SAFE_INTEGER_PARSE_OUT_OF_RANGE;
    }

    if (end == text || *end != '\0') {
        return SAFE_INTEGER_PARSE_INVALID_FORMAT;
    }

    *value = (int32_t)parsed;
    return SAFE_INTEGER_PARSE_OK;
}
