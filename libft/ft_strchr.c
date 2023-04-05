/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icario <icario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 18:00:28 by icario            #+#    #+#             */
/*   Updated: 2023/01/19 11:21:33 by icario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <string.h>
#include <stdio.h>

char	*ft_strchr(char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s != '\0')
	{
		if (*s == (char)c)
			return (s);
		s++;
	}
	return (NULL);
}
/*
int	main(void)
{
	char s[] = "tripouille";
	printf("%s\n", ft_strchr(s, 't' + 256));
	printf("%s\n", strchr(s, 't' + 256));
	return (0);
}*/
