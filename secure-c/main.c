#include "safe_copy.h"
#include "safe_integer.h"

#include <inttypes.h>
#include <stdio.h>
#include <string.h>

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
 * @brief Demonstrate a bounded copy into a fixed-size destination buffer.
 *
 * @return 0 when the copy succeeds; nonzero if the destination is too small.
 */
static int run_safe_copy_demo(void)
{
    char destination[16] = {0};
    safe_copy_result_t result =
        safe_copy(destination, sizeof(destination), "bounded copy");

    if (result != SAFE_COPY_OK) {
        fputs("Could not copy the example string safely.\n", stderr);
        return 1;
    }

    printf("Copied value: %s\n", destination);
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
int main(int argc, char *argv[])
{
    if (argc > 1 && strcmp(argv[1], "safe_copy") == 0) {
        return run_safe_copy_demo();
    }

    return run_safe_integer_demo();
}