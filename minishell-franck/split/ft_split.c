/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 08:20:57 by nbled             #+#    #+#             */
/*   Updated: 2023/02/23 08:20:59 by nbled            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_split(const char *s)
{
	char	**tab;
	int		size;
	size_t	i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	size = ft_count_words(s);
	tab = malloc(sizeof(char *) * (size + 1));
	if (!tab)
		return (NULL);
	while (i < ft_count_words(s))
	{
		while (s[j] && s[j] == ' ')
			j++;
		tab[i] = malloc(ft_str_len(s + j) + 1);
		k = 0;
		if (s[j] == 39)
		{
			j++;
			while (s[j] && s[j] != 39)
				tab[i][k++] = s[j++];
			j++;
		}
		else if (s[j] == 34)
		{
			j++;
			while (s[j] && s[j] != 34)
				tab[i][k++] = s[j++];
			j++;
		}
		else if (isasep(s[j]))
		{
			tab[i][k++] = s[j++];
			if (s[j] && s[j - 1] && s[j] == '<' && s[j - 1] == '<')
				tab[i][k++] = s[j++];
			if (s[j] && s[j - 1] && s[j] == '>' && s[j - 1] == '>')
				tab[i][k++] = s[j++];
		}
		else
			while (s[j] && s[j] != ' ' && !isasep(s[j]))
				tab[i][k++] = s[j++];
		tab[i][k] = '\0';
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
