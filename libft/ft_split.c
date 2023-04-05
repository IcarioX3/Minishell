/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icario <icario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 11:34:24 by icario            #+#    #+#             */
/*   Updated: 2023/02/05 16:06:25 by icario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

int	ft_wcount(char *s, char c)
{
	int	wcount;
	int	state;

	wcount = 0;
	state = 1;
	if (!s)
		return (-1);
	while (*s != '\0')
	{
		if (state && *s != c)
		{
			wcount++;
			state = 0;
		}
		if (*s == c)
			state = 1;
		s++;
	}
	return (wcount);
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	**ft_split(char *s, char c)
{
	char	**split;
	int		i;
	int		j;
	int		k;

	split = malloc((ft_wcount(s, c) + 1) * sizeof(char *));
	if (ft_wcount(s, c) == -1 || !split)
		return (NULL);
	i = -1;
	j = 0;
	k = -1;
	while (++i <= ft_strlen(s))
	{
		if (s[i] != c && k < 0)
			k = i;
		else if ((s[i] == c || i == ft_strlen(s)) && k >= 0)
		{
			split[j++] = ft_substr(s, k, i - k);
			if (!split[j - 1])
				return (free_split(split), NULL);
			k = -1;
		}
	}
	split[j] = NULL;
	return (split);
}
/*
int	main(void)
{
	char	**split;
	char	s[] = "ll,l";
	char	sep = ',';
	int	i = 0;
	int	wcount = ft_wcount(s, sep);

	split = ft_split(s, sep);
	printf("nombre de mots: %d\n", wcount);
	while (i < wcount)
	{
		printf("%s\n", split[i]);
		i++;
	}
	return (0);
}*/
