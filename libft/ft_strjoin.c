/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablevin <ablevin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 12:19:50 by ablevin           #+#    #+#             */
/*   Updated: 2023/04/14 11:44:33 by ablevin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s;

	if (!s2)
		return (NULL);
	if (!s1)
	{
		s = malloc((ft_strlen(s2) + 1) * sizeof(char));
		if (!s)
			return (NULL);
		ft_strlcpy(s, s2, ft_strlen(s2) + 1);
		return (s);
	}
	s = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!s)
		return (NULL);
	ft_strlcpy(s, s1, ft_strlen(s1) + 1);
	ft_strlcat(s, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	s[ft_strlen(s)] = '\0';
	free(s1);
	return (s);
}
/*
int	main(void)
{
	printf("%s", ft_strjoin("", "42"));
	return (0);
}*/
