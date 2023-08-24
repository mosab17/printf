#include "main.h"

/****************** PRINT POINTER ******************/
int print_memory_address(va_list arg_list, char buffer_array[], int active_flags,
	int char_width, int precision_value, int type_size)
{
	char additional_char = 0, padding_char = ' ';
	int buffer_idx = BUFFER_SIZE - 2, address_length = 2; /* address_length=2, for '0x' */
	unsigned long addr_numeric;
	char hex_map[] = "0123456789abcdef";
	void *address_ptr = va_arg(arg_list, void *);

	UNUSED(char_width);
	UNUSED(type_size);

	if (address_ptr == NULL)
		return (write(1, "(nil)", 5));

	buffer_array[BUFFER_SIZE - 1] = '\0';
	UNUSED(precision_value);

	addr_numeric = (unsigned long)address_ptr;

	while (addr_numeric > 0)
	{
		buffer_array[buffer_idx--] = hex_map[addr_numeric % 16];
		addr_numeric /= 16;
		address_length++;
	}

	if ((active_flags & F_ZERO) && !(active_flags & F_MINUS))
		padding_char = '0';
	if (active_flags & F_PLUS)
		additional_char = '+', address_length++;
	else if (active_flags & F_SPACE)
		additional_char = ' ', address_length++;

	buffer_idx++;

	return (write_pointer(buffer_array, buffer_idx, address_length,
		char_width, active_flags, padding_char, additional_char, 1));
}

/************************* PRINT NON PRINTABLE *************************/
int print_ascii_in_hex(va_list arg_list, char buffer_array[],
	int active_flags, int char_width, int precision_value, int type_size)
{
	int str_idx = 0, hex_offset = 0;
	char *input_str = va_arg(arg_list, char *);

	UNUSED(active_flags);
	UNUSED(char_width);
	UNUSED(precision_value);
	UNUSED(type_size);

	if (input_str == NULL)
		return (write(1, "(null)", 6));

	while (input_str[str_idx] != '\0')
	{
		if (is_printable(input_str[str_idx]))
			buffer_array[str_idx + hex_offset] = input_str[str_idx];
		else
			hex_offset += append_hexa_code(input_str[str_idx], buffer_array, str_idx + hex_offset);

		str_idx++;
	}

	buffer_array[str_idx + hex_offset] = '\0';

	return (write(1, buffer_array, str_idx + hex_offset));
}

/************************* PRINT REVERSE *************************/
int print_string_reverse(va_list arg_list, char buffer_array[],
	int active_flags, int char_width, int precision_value, int type_size)
{
	char *input_str;
	int str_len, char_count = 0;

	UNUSED(buffer_array);
	UNUSED(active_flags);
	UNUSED(char_width);
	UNUSED(type_size);

	input_str = va_arg(arg_list, char *);

	if (input_str == NULL)
	{
		UNUSED(precision_value);
		input_str = ")Null(";
	}
	for (str_len = 0; input_str[str_len]; str_len++)
		;

	for (str_len = str_len - 1; str_len >= 0; str_len--)
	{
		char single_char = input_str[str_len];
		write(1, &single_char, 1);
		char_count++;
	}
	return (char_count);
}

/************************* PRINT A STRING IN ROT13 *************************/
int print_rot13_encoded(va_list arg_list, char buffer_array[],
	int active_flags, int char_width, int precision_value, int type_size)
{
	char transformed_char;
	char *input_str;
	unsigned int str_idx, map_idx;
	int char_count = 0;
	char original[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char transformed[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	input_str = va_arg(arg_list, char *);
	UNUSED(buffer_array);
	UNUSED(active_flags);
	UNUSED(char_width);
	UNUSED(precision_value);
	UNUSED(type_size);

	if (input_str == NULL)
		input_str = "(AHYY)";
	for (str_idx = 0; input_str[str_idx]; str_idx++)
	{
		for (map_idx = 0; original[map_idx]; map_idx++)
		{
			if (original[map_idx] == input_str[str_idx])
			{
				transformed_char = transformed[map_idx];
				write(1, &transformed_char, 1);
				char_count++;
				break;
			}
		}
		if (!original[map_idx])
		{
			transformed_char = input_str[str_idx];
			write(1, &transformed_char, 1);
			char_count++;
		}
	}
	return (char_count);
}
