#include "safe_copy.h"

#include <stdio.h>
#include <string.h>

static int check_case(
    const char *label,
    char *buffer,
    size_t buffer_size,
    const char *source,
    safe_copy_result_t expected_result,
    const char *expected_text)
{
    const char initial_text[] = "UNCHANGED";
    safe_copy_result_t actual_result;

    strcpy(buffer, initial_text);
    actual_result = safe_copy(buffer, buffer_size, source);

    if (actual_result != expected_result) {
        fprintf(
            stderr,
            "%s: expected result %d but got %d\n",
            label,
            expected_result,
            actual_result);
        return 1;
    }

    if (strcmp(buffer, expected_text) != 0) {
        fprintf(
            stderr,
            "%s: expected buffer %s but got %s\n",
            label,
            expected_text,
            buffer);
        return 1;
    }

    return 0;
}

int main(void)
{
    char exact[6];
    char small[5];
    char null_buffer[16];
    int failures = 0;

    failures += check_case(
        "exact-fit",
        exact,
        sizeof(exact),
        "hello",
        SAFE_COPY_OK,
        "hello");

    failures += check_case(
        "too-small",
        small,
        sizeof(small),
        "hello",
        SAFE_COPY_BUFFER_TOO_SMALL,
        "UNCHANGED");

    failures += check_case(
        "empty-source",
        null_buffer,
        sizeof(null_buffer),
        "",
        SAFE_COPY_OK,
        "");

    if (safe_copy(NULL, 16, "hello") != SAFE_COPY_INVALID_ARGUMENT) {
        fprintf(stderr, "null-destination: expected INVALID_ARGUMENT\n");
        ++failures;
    }

    if (safe_copy(null_buffer, 16, NULL) != SAFE_COPY_INVALID_ARGUMENT) {
        fprintf(stderr, "null-source: expected INVALID_ARGUMENT\n");
        ++failures;
    }

    if (safe_copy(null_buffer, 0, "hello") != SAFE_COPY_INVALID_ARGUMENT) {
        fprintf(stderr, "zero-length: expected INVALID_ARGUMENT\n");
        ++failures;
    }

    if (failures != 0) {
        fprintf(stderr, "%d safe-copy test(s) failed\n", failures);
        return 1;
    }

    puts("safe_copy tests passed");
    return 0;
}
