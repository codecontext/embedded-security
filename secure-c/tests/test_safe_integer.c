#include "safe_integer.h"

#include <stdio.h>

/**
 * @brief Check one parser result, value, and failure-state guarantee.
 *
 * @details
 * The output starts at a sentinel value. Successful parses must replace it
 * with the expected value; failed parses must leave it untouched. This
 * checks both the API result and its transactional output behavior.
 *
 * @param[in] text Input string, or null for the null-input test.
 * @param[in] expected_result Expected parser result.
 * @param[in] expected_value Expected value when parsing succeeds.
 * @return 0 when the case passes; 1 when an expectation fails.
 */
static int check_parse_case(
    const char *text,
    safe_integer_parse_result_t expected_result,
    int32_t expected_value)
{
    const int32_t initial_value = INT32_C(77);
    int32_t value = initial_value;
    safe_integer_parse_result_t actual_result =
        parse_int32_decimal(text, &value);

    if (actual_result != expected_result) {
        fprintf(stderr, "Unexpected parse result for input: %s\n",
                text == NULL ? "(null)" : text);
        return 1;
    }

    if (expected_result == SAFE_INTEGER_PARSE_OK) {
        if (value != expected_value) {
            fprintf(stderr, "Unexpected value for input: %s\n", text);
            return 1;
        }
    } else if (value != initial_value) {
        fprintf(stderr, "Output changed after parse failure.\n");
        return 1;
    }

    return 0;
}

/**
 * @brief Verify that a null output pointer is rejected.
 * @return 0 when the argument is rejected; 1 otherwise.
 */
static int check_null_output(void)
{
    safe_integer_parse_result_t result =
        parse_int32_decimal("1", NULL);

    if (result != SAFE_INTEGER_PARSE_INVALID_ARGUMENT) {
        fprintf(stderr, "Null output pointer was not rejected.\n");
        return 1;
    }

    return 0;
}

/**
 * @brief Run parser boundary, syntax, and argument tests.
 *
 * @details
 * Covers zero and signed values, both int32_t endpoints, out-of-range values,
 * a very large numeric string, null arguments, empty/sign-only strings,
 * whitespace, trailing characters, and a non-decimal prefix.
 *
 * @return 0 when all test cases pass; nonzero when any case fails.
 */
int main(void)
{
    int failures = 0;

    failures += check_parse_case(
        "0", SAFE_INTEGER_PARSE_OK, INT32_C(0));
    failures += check_parse_case(
        "+17", SAFE_INTEGER_PARSE_OK, INT32_C(17));
    failures += check_parse_case(
        "-17", SAFE_INTEGER_PARSE_OK, INT32_C(-17));
    failures += check_parse_case(
        "2147483647", SAFE_INTEGER_PARSE_OK, INT32_MAX);
    failures += check_parse_case(
        "-2147483648", SAFE_INTEGER_PARSE_OK, INT32_MIN);

    failures += check_parse_case(
        "2147483648", SAFE_INTEGER_PARSE_OUT_OF_RANGE, INT32_C(0));
    failures += check_parse_case(
        "-2147483649", SAFE_INTEGER_PARSE_OUT_OF_RANGE, INT32_C(0));
    failures += check_parse_case(
        "999999999999999999999999999999999999999999",
        SAFE_INTEGER_PARSE_OUT_OF_RANGE,
        INT32_C(0));

    failures += check_parse_case(
        NULL, SAFE_INTEGER_PARSE_INVALID_ARGUMENT, INT32_C(0));
    failures += check_parse_case(
        "", SAFE_INTEGER_PARSE_INVALID_FORMAT, INT32_C(0));
    failures += check_parse_case(
        "+", SAFE_INTEGER_PARSE_INVALID_FORMAT, INT32_C(0));
    failures += check_parse_case(
        "-", SAFE_INTEGER_PARSE_INVALID_FORMAT, INT32_C(0));
    failures += check_parse_case(
        " 12", SAFE_INTEGER_PARSE_INVALID_FORMAT, INT32_C(0));
    failures += check_parse_case(
        "12 ", SAFE_INTEGER_PARSE_INVALID_FORMAT, INT32_C(0));
    failures += check_parse_case(
        "12x", SAFE_INTEGER_PARSE_INVALID_FORMAT, INT32_C(0));
    failures += check_parse_case(
        "0x10", SAFE_INTEGER_PARSE_INVALID_FORMAT, INT32_C(0));

    failures += check_null_output();

    if (failures != 0) {
        fprintf(stderr, "%d parser test(s) failed.\n", failures);
        return 1;
    }

    puts("All safe integer parser tests passed.");
    return 0;
}
