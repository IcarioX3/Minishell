/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 08:27:02 by nbled             #+#    #+#             */
/*   Updated: 2023/02/23 08:27:04 by nbled            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_count_words(const char *s)
{
	size_t	words;
	//int		quote;
	int		i;

	i = 0;
	//quote = 0;
	words = 0;
	while (s[i])
	{
		while (s[i] && s[i] == ' ')
			i++;
		if (s[i] && s[i] != ' ')
		{
			words++;
			if (s[i] == 39)
			{
				i++;
				while (s[i] && s[i] != 39)
					i++;
				i++;
			}
			else if (s[i] == 34)
			{
				i++;
				while (s[i] && s[i] != 34)
					i++;
				i++;
			}
			else if (isasep(s[i]))
			{
				i++;
				if (s[i] && s[i - 1] && s[i] == '<' && s[i - 1] == '<')
					i++;
				if (s[i] && s[i - 1] && s[i] == '>' && s[i - 1] == '>')
					i++;
			}
			else
				while (s[i] && s[i] != ' ' && !isasep(s[i]))
					i++;
		}
	}
	return (words);
}
