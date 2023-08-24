#include "main.h"

void flushBuffer(char buf[], int *bufIndex);

/**
 * _printf - Printf function
 * @format: format.
 * Return: Printed chars.
 */
int _printf(const char *format, ...)
{
	int idx, charsThisLoop = 0, totalCharsPrinted = 0;
	int fmtFlags, fmtWidth, fmtPrecision, fmtSize, bufIndex = 0;
	va_list argList;
	char buf[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(argList, format);

	for (idx = 0; format && format[idx] != '\0'; idx++)
	{
		if (format[idx] != '%')
		{
			buf[bufIndex++] = format[idx];
			if (bufIndex == BUFF_SIZE)
				flushBuffer(buf, &bufIndex);
			totalCharsPrinted++;
		}
		else
		{
			flushBuffer(buf, &bufIndex);
			fmtFlags = get_flags(format, &idx);
			fmtWidth = get_width(format, &idx, argList);
			fmtPrecision = get_precision(format, &idx, argList);
			fmtSize = get_size(format, &idx);
			++idx;
			charsThisLoop = handle_print(format, &idx, argList, buf,
				fmtFlags, fmtWidth, fmtPrecision, fmtSize);
			if (charsThisLoop == -1)
				return (-1);
			totalCharsPrinted += charsThisLoop;
		}
	}

	flushBuffer(buf, &bufIndex);

	va_end(argList);

	return (totalCharsPrinted);
}

/**
 * flushBuffer - Prints the contents of the buffer if it exist
 * @buf: Array of chars
 * @bufIndex: Index at which to add next char, represents the length.
 */
void flushBuffer(char buf[], int *bufIndex)
{
	if (*bufIndex > 0)
		write(1, buf, *bufIndex);

	*bufIndex = 0;
}
