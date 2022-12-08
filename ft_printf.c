/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 10:26:29 by lclerc            #+#    #+#             */
/*   Updated: 2022/12/08 17:44:40 by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
/* FIXME: remove stdio in HEADER */

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

	i = 0;
	length =0;
	if (s == NULL)
	{
		i += write(1, "(null)", 6);
		return (i);
	}
	length = ft_strlen(s);	
	while ( i < length)
	{
		i += ft_putchar(*s++);
	}
	return i;
}

int ft_print_pointer(size_t n)
{
	int	i;

	i = 0;
	i += ft_putstr("0x");
	i += ft_putnbr_pointer(n);
	return (i);
}


int	format_me(va_list arg_pointer, const char *format)
{
	int			i;
	//const char 	*s;

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
		i = ft_putnbr_hexa_lower(va_arg(arg_pointer, unsigned int));
	if (*format == 'X')
		i = ft_putnbr_hexa_upper(va_arg(arg_pointer,  unsigned int));
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

