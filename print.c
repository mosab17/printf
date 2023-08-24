#include "main.h"

/**
 * process_format_specifier - Prints an argument based on its type
 * @format_str: Formatted string in which to print the arguments.
 * @current_idx: Pointer to current index in the format string.
 * @args_list: List of arguments to be printed.
 * @output_buffer: Buffer array to handle print.
 * @active_flags: Calculates active flags.
 * @specified_width: Specified width for printing.
 * @specified_precision: Specified precision for printing.
 * @specified_size: Size specifier.
 * Return: 1 or 2;
 */
int process_format_specifier(const char *format_str, int *current_idx, va_list args_list, char output_buffer[],
	int active_flags, int specified_width, int specified_precision, int specified_size)
{
	int type_idx, unrecognized_length = 0, number_of_chars_printed = -1;
	fmt_t format_types[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};
	for (type_idx = 0; format_types[type_idx].fmt != '\0'; type_idx++)
		if (format_str[*current_idx] == format_types[type_idx].fmt)
			return (format_types[type_idx].fn(args_list, output_buffer, active_flags, specified_width, specified_precision, specified_size));

	if (format_types[type_idx].fmt == '\0')
	{
		if (format_str[*current_idx] == '\0')
			return (-1);
		unrecognized_length += write(1, "%%", 1);
		if (format_str[*current_idx - 1] == ' ')
			unrecognized_length += write(1, " ", 1);
		else if (specified_width)
		{
			--(*current_idx);
			while (format_str[*current_idx] != ' ' && format_str[*current_idx] != '%')
				--(*current_idx);
			if (format_str[*current_idx] == ' ')
				--(*current_idx);
			return (1);
		}
		unrecognized_length += write(1, &format_str[*current_idx], 1);
		return (unrecognized_length);
	}
	return (number_of_chars_printed);
}

