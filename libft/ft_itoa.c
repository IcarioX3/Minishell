/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablevin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:52:13 by ablevin           #+#    #+#             */
/*   Updated: 2022/06/07 20:11:02 by icario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

int	ft_itoasize(int n)
{
	int	size;

	size = 0;
	if (n < 0 && n > -2147483648)
	{
		size++;
		n = -n;
	}
	else if (n == 0)
		return (1);
	else if (n == -2147483648)
		return (11);
	while (n >= 1)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char	*s;
	int		i;
	int		size;
	long	num;

	num = n;
	size = ft_itoasize(num);
	s = malloc((size + 1) * sizeof(char));
	if (!s)
		return (NULL);
	if (num < 0)
	{
		s[0] = '-';
		num = -num;
	}
	i = 1;
	if (num == 0)
		s[0] = '0';
	while (num >= 1)
	{
		s[size - i] = (num % 10) + '0';
		num /= 10;
		i++;
	}
	return (s[size] = '\0', s);
}
/*
int	main(void)
{
	printf("%s", ft_itoa(-2147483648));
	return (0);
}*/
