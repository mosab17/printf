#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define UNUSED(x) (void)(x)
#define BUFF_SIZE 1024


#defineFl_MINUS 1
#defineFl_PLUS 2
#defineFl_ZERO 4
#defineFl_HASH 8
#defineFl_SPACE 16

#define S_LONG 2
#define S_SHORT 1

/**
 * struct fmmt - Struct op
 *
 * @fmmt: The format.
 * @fn: The function associated.
 */
struct fmmt
{
	char fmmt;
	int (*fn)(va_list, char[], int, int, int, int);
};


/**
 * typedef struct fmmt fmmt_t - Struct op
 *
 * @fmmt: The format.
 * @fm_t: The function associated.
 */
typedef struct fmmt fmmt_t;

int _printf(const char *format, ...);
int handle_print(const char *fmmt, int *i,
va_list list, char buffer[], int flags, int width, int precision, int size);


int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size);


int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size);

int print_hexa(va_list types, char map_to[],
char buffer[], int flags, char flag_ch, int width, int precision, int size);

int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size);


int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size);


int get_flags(const char *format, int *i);
int get_width(const char *format, int *i, va_list list);
int get_precision(const char *format, int *i, va_list list);
int get_size(const char *format, int *i);


int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size);


int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size);


int handle_write_char(char c, char buffer[],
	int flags, int width, int precision, int size);
int write_number(int is_positive, int ind, char buffer[],
	int flags, int width, int precision, int size);
int write_num(int ind, char bff[], int flags, int width, int precision,
	int length, char padd, char extra_c);
int write_pointer(char buffer[], int ind, int length,
	int width, int flags, char padd, char extra_c, int padd_start);

int write_unsgnd(int is_negative, int ind,
char buffer[],
	int flags, int width, int precision, int size);


int is_printable(char);
int append_hexa_code(char, char[], int);
int is_digit(char);

long int convert_size_number(long int num, int size);
long int convert_size_unsgnd(unsigned long int num, int size);

#endif /* MAIN_H */




