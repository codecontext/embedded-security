/**
 * @file caesar_cipher.c
 * @brief Educational Caesar rotation for alphabetic text.
 *
 * @details
 * The Caesar cipher shifts each alphabetic character by a fixed amount. For a
 * letter in the range A-Z or a-z, the code computes the offset from the base of
 * the alphabet, adds the shift, and wraps back to the beginning when the value
 * would pass beyond Z or z. Non-letter characters are left unchanged.
 *
 * For a shift of +3, the alphabet mapping is:
 *
 * @code
 * Plain:  A B C D ... W X Y Z
 * Cipher: D E F G ... Z A B C
 * @endcode
 *
 * For example, H is 7 positions after A. Adding 3 gives position 10, or K:
 *
 * @code
 * H E L L O
 * | | | | |
 * K H O O R
 * @endcode
 *
 * The formula for a letter with alphabet offset x is
 * (x + normalized_shift) modulo 26. The same mapping is applied separately
 * to uppercase and lowercase letters, preserving their case.
 *
 * The shift is normalized modulo 26 so that a large positive or negative value
 * still maps to a valid rotation in the same alphabet. The function validates
 * the input buffer and its size before writing so that every call either
 * succeeds safely or fails without corrupting caller data.
 */
#include "caesar_cipher.h"

#include <stddef.h>

static int rotate_letter(char letter, int shift)
{
    const int alphabet_size = 26;
    const int base = (letter >= 'A' && letter <= 'Z') ? 'A' : 'a';
    int offset;

    if (letter < 'A' || (letter > 'Z' && letter < 'a') || letter > 'z') {
        return letter;
    }

    offset = (int)(letter - base);
    offset = (offset + shift) % alphabet_size;
    if (offset < 0) {
        offset += alphabet_size;
    }

    return base + offset;
}

caesar_result_t caesar_rotate(char *text,
                              size_t text_size,
                              int shift)
{
    size_t i;
    size_t normalized_shift;

    if (text == NULL || text_size == 0U) {
        return CAESAR_INVALID_ARGUMENT;
    }

    // Normalize the shift to [0, 25] to simplify the mapping.
    normalized_shift = (size_t)((shift % 26 + 26) % 26);

    for (i = 0U; i < text_size; ++i) {
        if (text[i] == '\0') {
            return CAESAR_OK;
        }

        text[i] = (char)rotate_letter(text[i], (int)normalized_shift);
    }

    return CAESAR_BUFFER_TOO_SMALL;
}
