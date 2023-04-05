/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablevin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 22:52:29 by ablevin           #+#    #+#             */
/*   Updated: 2022/12/02 17:43:30 by ablevin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>

int	ft_putnbr_base_p(unsigned long long nb, char *base, int isint)
{
	unsigned int	len;
	static int		size;

	size = 0;
	len = ft_strlen(base);
	if (isint)
		nb = (unsigned int) nb;
	if (nb < len)
		ft_putchar_fd(base[nb], 1);
	if (nb >= len)
	{
		ft_putnbr_base_p(nb / len, base, isint);
		ft_putchar_fd(base[nb % len], 1);
	}
	size++;
	return (size);
}

int	ft_printf_str(va_list ap)
{
	char	*str;

	str = va_arg(ap, char *);
	if (!str)
		return (write(1, "(null)", 6));
	ft_putstr_fd(str, 1);
	return (ft_strlen(str));
}

int	ft_printf_int(va_list ap, char type)
{
	int long		nb;
	int				isneg;
	unsigned int	uint;

	isneg = 0;
	if (type == 'd' || type == 'i')
	{
		nb = va_arg(ap, int);
		if (nb < 0)
		{
			nb *= -1;
			ft_putchar_fd('-', 1);
			isneg = 1;
		}
		return (ft_putnbr_base_p(nb, "0123456789", 0) + isneg);
	}
	uint = va_arg(ap, unsigned int);
	return (ft_putnbr_base_p(uint, "0123456789", 1));
}

int	ft_print_hex(va_list ap, char type)
{
	unsigned long long	p;
	int					hex;

	if (type == 'p')
	{
		p = va_arg(ap, unsigned long long);
		if (p == 0)
			return (write(1, "(nil)", 5));
		ft_putstr_fd("0x", 1);
		return (ft_putnbr_base_p(p, "0123456789abcdef", 0) + 2);
	}
	if (type == 'x' || type == 'X')
	{
		hex = va_arg(ap, int);
		if (type == 'x')
			return (ft_putnbr_base_p(hex, "0123456789abcdef", 1));
		else
			return (ft_putnbr_base_p(hex, "0123456789ABCDEF", 1));
	}
	return (0);
}

int	ft_parsing(va_list ap, char type)
{
	if (type == 'c')
		return (ft_putchar_fd(va_arg(ap, int), 1), 1);
	if (type == 's')
		return (ft_printf_str(ap));
	if (type == 'p')
		return (ft_print_hex(ap, type));
	if (type == 'd' || type == 'i')
		return (ft_printf_int(ap, type));
	if (type == 'u')
		return (ft_printf_int(ap, type));
	if (type == 'x' || type == 'X')
		return (ft_print_hex(ap, type));
	if (type == '%')
		return (write(1, "%", 1));
	return (0);
}
