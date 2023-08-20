#include "main.h"

/**
 * get_flags - Calculates active flags
 * @format: Formatted string in which to print the arguments
 * @i: take a parameter.
 * Return: Flags:
 */
int get_flags(const char *format, int *i)
{
	int j, currnt_i;
	int flags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {Fl_MINUS, Fl_PLUS, Fl_ZERO, Fl_HASH, Fl_SPACE, 0};

	for (currnt_i = *i + 1; format[currnt_i] != '\0'; currnt_i++)
	{
		for (j = 0; FLAGS_CH[j] != '\0'; j++)
			if (format[currnt_i] == FLAGS_CH[j])
			{
				flags |= FLAGS_ARR[j];
				break;
			}

		if (FLAGS_CH[j] == 0)
			break;
	}

	*i = currnt_i - 1;

	return (flags);
}







