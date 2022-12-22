/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:10:18 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/22 14:35:03 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_str(char *str, char c, int mode)
{
	int	len;

	if (mode)
	{
		if (str)
		{
			len = 0;
			while (str[len++])
				;
			return (write(1, str, len - 1));
		}
		else
			return (write(1, "(null)", 6));
	}
	else
	{
		return (write(1, &c, 1));
	}
}

void	ft_putnbr(int64_t n, int base, char *charset, int *len)
{
	if (n < 0)
	{
		*len += write(1, "-", 1);
		n = -n;
	}
	if (n >= base)
		ft_putnbr(n / base, base, charset, len);
	*len += write(1, &charset[n % base], 1);
}

void	ft_putptr(uintptr_t n, uintptr_t base, char *charset, int *len)
{
	if (n >= base)
		ft_putptr(n / base, base, charset, len);
	*len += write(1, &charset[n % base], 1);
}

int	eval_format(const char *format, va_list ap, int *len, int i)
{
	if (format[i] == 'c')
		*len += ft_print_str(NULL, va_arg(ap, int), 0);
	else if (format[i] == 's')
		*len += ft_print_str(va_arg(ap, char *), 0, 1);
	else if (format[i] == 'd' || format[i] == 'i')
		ft_putnbr(va_arg(ap, int), 10, "0123456789", len);
	else if (format[i] == 'x')
		ft_putnbr(va_arg(ap, unsigned int), 16, "0123456789abcdef", len);
	else if (format[i] == 'X')
		ft_putnbr(va_arg(ap, unsigned int), 16, "0123456789ABCDEF", len);
	else if (format[i] == 'u')
		ft_putnbr(va_arg(ap, unsigned int), 10, "0123456789", len);
	else if (format[i] == 'p')
	{
		*len += write(1, "0x", 2);
		ft_putptr(va_arg(ap, uintptr_t), 16, "0123456789abcdef", len);
	}
	else if (format[i] == '%')
		*len += write(1, "%%", 1);
	else
		return (0);
	return (1);
}

int	ft_printf(const char *format, ...)
{
	va_list		ap;
	int			i;
	int			len;

	i = 0;
	len = 0;
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i += eval_format(format, ap, &len, i + 1);
		}
		else
			len += write(1, &format[i], 1);
		i++;
	}
	va_end(ap);
	return (len);
}
