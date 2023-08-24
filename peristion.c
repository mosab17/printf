#include "main.h"

/**
 * get_precision_value - Calculates the precision for printing
 * @formatted_string: Formatted string in which to print the arguments
 * @format_index: Pointer to current index in formatted string.
 * @args_list: List of arguments.
 *
 * Return: Precision value.
 */
int get_precision_value(const char *formatted_string, int *format_index, va_list args_list)
{
	int current_index = *format_index + 1;
	int calculated_precision = -1;

	if (formatted_string[current_index] != '.')
		return (calculated_precision);

	calculated_precision = 0;

	for (current_index += 1; formatted_string[current_index] != '\0'; current_index++)
	{
		if (is_digit(formatted_string[current_index]))
		{
			calculated_precision *= 10;
			calculated_precision += formatted_string[current_index] - '0';
		}
		else if (formatted_string[current_index] == '*')
		{
			current_index++;
			calculated_precision = va_arg(args_list, int);
			break;
		}
		else
			break;
	}

	*format_index = current_index - 1;

	return (calculated_precision);
}

