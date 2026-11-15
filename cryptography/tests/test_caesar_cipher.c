#include "caesar_cipher.h"

#include <stdio.h>
#include <string.h>

static int check_rotation(
    const char *label,
    const char *input,
    int shift,
    const char *expected)
{
    char buffer[128] = {0};
    int result;

    strncpy(buffer, input, sizeof(buffer) - 1U);
    result = caesar_rotate(buffer, sizeof(buffer), shift);

    if (result != CAESAR_OK) {
        fprintf(stderr, "%s: expected CAESAR_OK but got %d\n", label, result);
        return 1;
    }

    if (strcmp(buffer, expected) != 0) {
        fprintf(stderr, "%s: expected '%s' but got '%s'\n", label, expected, buffer);
        return 1;
    }

    return 0;
}

int main(void)
{
    int failures = 0;

    failures += check_rotation("plain", "HELLO", 3, "KHOOR");
    failures += check_rotation("wrap", "XYZ", 3, "ABC");
    failures += check_rotation("mixed", "Hello, World!", 3, "Khoor, Zruog!");

    if (caesar_rotate(NULL, 16, 3) != CAESAR_INVALID_ARGUMENT) {
        fprintf(stderr, "null-buffer: expected INVALID_ARGUMENT\n");
        ++failures;
    }

    if (caesar_rotate("ABC", 0U, 3) != CAESAR_INVALID_ARGUMENT) {
        fprintf(stderr, "zero-length: expected INVALID_ARGUMENT\n");
        ++failures;
    }

    if (failures != 0) {
        fprintf(stderr, "%d caesar_cipher test(s) failed\n", failures);
        return 1;
    }

    puts("caesar_cipher tests passed");
    return 0;
}
