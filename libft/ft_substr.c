/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablevin <ablevin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:32:00 by icario            #+#    #+#             */
/*   Updated: 2023/01/25 13:51:44 by ablevin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "libft.h"
#include <stdio.h>

char	*ft_substr(char *s, int start, int len)
{
	char	*substr;
	int		i;
	int		size;

	i = 0;
	if (!s)
		return (NULL);
	if (ft_strlen(s) - start < len)
		size = ft_strlen(s) - start;
	else
		size = len;
	if (start > ft_strlen(s))
	{
		substr = malloc(1 * sizeof(char));
		return (substr[0] = '\0', substr);
	}
	substr = malloc((size + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	while (i < len && s[start + i] && start < ft_strlen(s))
	{
		substr[i] = s[start + i];
		i++;
	}
	return (substr[i] = '\0', substr);
}
/*
int main (void)
{
	char *str = "BOUM";
	char *ret = ft_substr(str, 100 ,1);
	printf("[%s]\n", ret);
	free(ret);
}*/
