/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablevin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:56:29 by ablevin           #+#    #+#             */
/*   Updated: 2022/05/10 17:53:40 by ablevin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <bsd/string.h>
#include <stdio.h>

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	int		len;

	i = 0;
	len = 0;
	while (src[len])
		len++;
	if (size == 0)
		return (len);
	while (i < (size - 1) && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (len);
}
/*
int	main(void)
{
	const char	src[20] = {"Hello World !"};
	char	dest[20] = {"World, Hello !"};
	const char	src1[20] = {"Hello World !"};
	char	dest1[20] = {"World, Hello !"};

	size_t	size = 15;
	printf("%ld\n", ft_strlcpy(dest, src, size));
	printf("%s\n", src);
	printf("%s\n", dest);
	printf("%ld\n", strlcpy(dest1, src1, size));
	printf("%s\n", src1);
	printf("%s\n", dest1);
	return (0);
}*/
