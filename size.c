#include "main.h"

/**
 * determine_argument_size - Calculates the size to cast the argument
 * @format_str: Formatted string in which to determine the argument size.
 * @current_idx: Current index pointer in the format_str.
 *
 * Return: Size specifier.
 */
int determine_argument_size(const char *format_str, int *current_idx)
{
    int temp_idx = *current_idx + 1;
    int cast_size = 0;

    if (format_str[temp_idx] == 'l')
        cast_size = S_LONG;
    else if (format_str[temp_idx] == 'h')
        cast_size = S_SHORT;

    if (cast_size == 0)
        *current_idx = temp_idx - 1;
    else
        *current_idx = temp_idx;

    return (cast_size);
}

