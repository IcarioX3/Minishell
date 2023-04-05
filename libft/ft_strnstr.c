/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icario <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 15:56:04 by icario            #+#    #+#             */
/*   Updated: 2022/05/16 14:46:34 by ablevin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <bsd/string.h>
#include <stdio.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (little[j] == '\0')
		return ((char *)big);
	while (big[i] && i < len)
	{
		while (little[j] == big[i + j] && little[j] != '\0' && (i + j) < len)
			j++;
		if (little[j] == '\0')
			return ((char *) big + i);
		else
			j = 0;
		i++;
	}
	return (NULL);
}
/*
int	main(int argc, char **argv)
{
	if (argc == 4)
	{
		printf("%s\n", ft_strnstr(argv[1], argv[2], atoi(argv[3])));
		printf("%s\n", strnstr(argv[1], argv[2], atoi(argv[3])));
	}
	return (0);
}*/
