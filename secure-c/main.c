#include "safe_integer.h"

#include <inttypes.h>
#include <stdio.h>

/**
 * @brief Demonstrate parsing a decimal value with the safe integer API.
 *
 * @details
 * The fixed example string keeps this executable deterministic. The return
 * status is checked before the parsed value is printed, demonstrating the
 * required caller pattern for handling untrusted text.
 *
 * @return 0 when parsing and output succeed; nonzero if parsing fails.
 */
static int run_safe_integer_demo(void)
{
    const char input[] = "12345";
    int32_t value = 0;
    safe_integer_parse_result_t result =
        parse_int32_decimal(input, &value);

    if (result != SAFE_INTEGER_PARSE_OK) {
        fputs("Could not parse the example integer.\n", stderr);
        return 1;
    }

    printf("Parsed value: %" PRId32 "\n", value);
    return 0;
}

/**
 * @brief Dispatch the Secure C learning demonstrations.
 *
 * @details
 * Keep each topic's demonstration in its own function so additional lessons
 * can be added without expanding the entry-point logic.
 *
 * @return The status returned by the selected demonstration.
 */
int main(void)
{
    return run_safe_integer_demo();
}