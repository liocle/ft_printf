/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 10:26:29 by lclerc            #+#    #+#             */
/*   Updated: 2022/12/07 17:31:39 by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* FIXME: remove stdio below */
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return 1;
}


size_t	ft_strlen(const char *s)
{
	char	*p;

	p = (char *)s;
	while (*p != '\0')
		p++;
	return (p - s);
}


int	ft_putstr(char *s)
{
	int	i;
	int	length;

	length = ft_strlen(s);	
	i = 0;
	if (s == NULL)
		i = write(1, "(null)", 6);
	{
		while ( i < length)
			i += ft_putchar(*s++);
	}
	//printf("s's length is :%i: ft_putstr's 'i' returns %d\n",length, i);
	return i;

}
int	ft_putnbr_hexa_lower(size_t n)
 {
 	unsigned int	i;
 
	//printf("My obtained n pointer is: %zu\n", n);
 	i =0;
 	if (n > 15)
 	{
 		i += ft_putnbr_hexa_lower(n / 16);
 		i += ft_putnbr_hexa_lower(n % 16);
 	}
 	if (n >= 0 && n <= 15 )
 	{
		if (n <= 9)
		{
 			i += ft_putchar(n + '0');
		}
		else 
 			i += ft_putchar(n - 10 + 'a');
 	}
 	return (i);
 }

int	ft_putnbr_hexa_upper(unsigned long n)
 {
 	unsigned int	i;
 
 	i =0;
 	if (n > 15)
 	{
 		i += ft_putnbr_hexa_upper(n / 16);
 		i += ft_putnbr_hexa_upper(n % 16);
 	}
 	if (n >= 0 && n < 15)
 	{
		if (n <= 9)
		{
 			i += ft_putchar(n + '0');
		}
		else 
 			i += ft_putchar(n - 10 + 'A');
 	}
 	return (i);
 }
 
int	ft_putnbr_unsigned(unsigned int n)
{
	int	i;

	i = 0;
	if (n > 9)
	{
		i += ft_putnbr_unsigned(n / 10);
		i += ft_putnbr_unsigned(n % 10);
	}
	if (n >= 0 && n <= 9)
		i += ft_putchar(n + '0');
	return (i);
}

int	ft_putnbr(int n)
{
	int	i;

	i =0;
	if (n < 0)
	{
		if (n == -2147483648)
		{
			i += ft_putchar('-');
			i += ft_putchar('2');
			n = 147483648;
		}
		else
		{
			i += ft_putchar('-');
			i += ft_putnbr(n * -1);
		}
	}
	if (n > 9)
	{
		i += ft_putnbr(n / 10);
		i += ft_putnbr(n % 10);
	}
	if (n >= 0 && n <= 9)
		i += ft_putchar(n + '0');
	return (i);
}

int ft_print_pointer(size_t n)
{
	int	i;

	i = 0;
	i += ft_putstr("0x");
	i += ft_putnbr_hexa_lower(n);
	return (i);
}


int	format_me(va_list arg_pointer, const char *format)
{
	int			i;
	const char 	*s;

	// Each call of va_arg returns one argument and steps 'arg_pointer' to
	// the next. The datatype in use determines what to return but also how
	// big pointer move to make to get to the next. Only int, doubles or 
	// pointers can be used (cant be self promoting type).
	if (*format == 'c') 
		i = ft_putchar(va_arg(arg_pointer, int));
	if (*format == 's')
		i = ft_putstr(va_arg(arg_pointer, char *));
	if (*format == 'd' || *format == 'i')
		i = ft_putnbr(va_arg(arg_pointer, int));
	if (*format == 'x')
		i = ft_putnbr_hexa_lower((size_t)va_arg(arg_pointer, int));
	if (*format == 'X')
		i = ft_putnbr_hexa_upper((unsigned long)va_arg(arg_pointer, int));
	if (*format == '%')
		i = ft_putchar('%');
	if (*format == 'u')
		i = ft_putnbr_unsigned(va_arg(arg_pointer, int));
	if (*format == 'p')
		i = ft_print_pointer((size_t)va_arg(arg_pointer, void *));
//printf("format_me's 'i' returns %d\n", i);
	return i;
}

int	ft_vprintf(va_list arg_pointer, const char	*format)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (format[j] != '\0')	
	{
		if (format[j] == '%')
		{
			i += format_me(arg_pointer , &format[++j]);
			j++;
		}
		else if(format[j] != '\0')
		{
			i += ft_putchar(format[j++]);
		}
	}
	//printf("     vprint loop -> i:%d: j:%d:\n " , i, j);	
	return (i); 
}



int	ft_printf(const char *format, ...)
{
	// the below va_list declares a variable that will refer to each argument in
	// turn.
	//
	// There MUST be at least 1 argument pointed at.
	va_list	arg_pointer;
	int		done;

	done = 0;
	// The arg_pointer is initialized by va_start to the 1st unamed argument.
	// va_start has to be called once before arg_pointer is used.
	va_start (arg_pointer, format);
	//in ft_vprintf, va_arg will be used.
	done = ft_vprintf(arg_pointer, format);
	// Needed to clean up, though could work without with GCC or clang
	va_end (arg_pointer);

//	printf("my printf returns done = %i\n", done);
	return done;
}

int	main(void)
{
	int year;
	char char_test;
	char *string;
	int negative;

	char_test = 'H';
	string = ":MY HOLIDAYS:";	
	year = 983742569;
	negative = -42;
	/* Testing NO specifyier */
	int	ft_printf_bare = ft_printf("_My ft_printf with no formating uses only putchar_\n");
	int	printf_bare = printf("_My ft_printf with no formating uses only putchar_\n");
	printf("My printf returns :%d:\nThe real one returns :%d:\n----------------\n",  ft_printf_bare, printf_bare);

	/* Testing CHARS */
	int ft_printf_char = ft_printf("_This 1st line is my ft_printf, testing chars :%c:, followed by real printf_\n", char_test);
	int printf_char = printf("_This 1st line is my ft_printf, testing chars :%c:, followed by real printf_\n", char_test);
	printf("My printf returns :%d:\nThe real one returns :%d:\n----------------\n",  ft_printf_char, printf_char);
	
	/* Testing CHARS */
	ft_printf_char = ft_printf("%s %c\n", "Hello", 'c');
	printf_char = printf("%s %c\n", "Hello", 'c');
	printf("My printf returns :%d:\nThe real one returns :%d:\n----------------\n",  ft_printf_char, printf_char);
	/* Testing CHARS */
	ft_printf_char = ft_printf("1234%c678\n", char_test);
	printf_char = printf("1234%c678\n", char_test);
	printf("My printf returns :%d:\nThe real one returns :%d:\n----------------\n",  ft_printf_char, printf_char);
	/* Testing STRINGS */
	int ft_printf_string = ft_printf("_This 1st line is my ft_printf, testing string :%s:, followed by real printf_\n", string);
	int printf_string = printf("_This 1st line is my ft_printf, testing string :%s:, followed by real printf_\n", string);
	printf("My printf returns :%d:\nThe real one returns :%d:\n----------------\n",  ft_printf_string, printf_string);

	/* Testing DIGITS */
	int	ft_printf_digit = ft_printf("It is soon :%d yesyes :%i:\n", year, year);
	int	printf_digit = printf("It is soon :%d yesyes :%i:\n", year, year);
	printf("My printf returns :%d:\nThe real one returns :%d:\n----------------\n",  ft_printf_digit, printf_digit);

	/* Testing HEXA */
	printf("Let's check %%x and %%X:\n");
	int	ft_printf_hexa = ft_printf("This year is :%i: what about it in hexa :%x: or even HEXA :%X:\n", year, year, year);
	int	printf_hexa = printf("This year is :%i: what about it in hexa :%x: or even HEXA :%X:\n", year, year, year);
	printf("My printf returns :%d:\nThe real one returns :%d:\n----------------\n",  ft_printf_hexa, printf_hexa);
	

	/* Testing unsigned int */
	int	ft_printf_unsigned = ft_printf("This year is :%u: and see what a negative %%, %u%%:\n", year, negative);
	int	printf_unsigned = printf("This year is :%u: and see what a negative %%, %u%%:\n", year, negative);
	printf("My printf returns :%d:\nThe real one returns :%d:\n----------------\n",  ft_printf_unsigned, printf_unsigned);

	/* Testing pointer */
	ft_printf_unsigned = ft_printf("My string location is: :%p:\n",  string );
	printf_unsigned = printf("My string location is: :%p:\n",  string );
	printf("My printf returns :%d:\nThe real one returns :%d:\n----------------\n",  ft_printf_unsigned, printf_unsigned);
	

	return 0;

}

