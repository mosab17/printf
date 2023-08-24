#include "main.h"

void buffer_print(char buf[], int *idx);

/**
 * _printf - Our custom printf function
 * @format: The format string
 * ...
 * Return: Number of characters printed
 */
int _printf(const char *format, ...)
{
    int i, chars_printed = 0, buffer_idx = 0;
    int fl, wid, prec, sz, tmp_printed;
    va_list args;
    char buf[BUFF_SIZE];

    if (!format)
        return (-1);

    va_start(args, format);

    for (i = 0; format[i]; i++)
    {
        if (format[i] != '%')
        {
            buf[buffer_idx++] = format[i];
            if (buffer_idx == BUFF_SIZE)
                buffer_print(buf, &buffer_idx);
            chars_printed++;
        }
        else
        {
            buffer_print(buf, &buffer_idx);
            fl = fetch_flags(format, &i);
            wid = fetch_width(format, &i, args);
            prec = fetch_precision(format, &i, args);
            sz = fetch_size(format, &i);
            i++;
            tmp_printed = print_arg(format, &i, args, buf, fl, wid, prec, sz);
            if (tmp_printed == -1)
                return (-1);
            chars_printed += tmp_printed;
        }
    }
    buffer_print(buf, &buffer_idx);
    va_end(args);
    return (chars_printed);
}

/**
 * buffer_print - Print buffer content if it's not empty
 * @buf: Buffer
 * @idx: Current buffer index
 */
void buffer_print(char buf[], int *idx)
{
    if (*idx > 0)
    {
        write(1, buf, *idx);
        *idx = 0;
    }
}

