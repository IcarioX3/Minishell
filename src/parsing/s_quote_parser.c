/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_quote_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablevin <ablevin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:04:23 by ablevin           #+#    #+#             */
/*   Updated: 2023/05/20 13:04:24 by ablevin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_string_s_quote(t_tokens *tokens)
{
	char	*str;

	str = NULL;
	if (tokens->token == S_QUOTE)
	{
		str = ft_strdup("");
		if (!str)
			return (NULL);
		return (str);
	}
	while (tokens && tokens->token != S_QUOTE)
	{
		str = ft_strjoin(str, tokens->str);
		tokens = tokens->next;
	}
	return (str);
}

t_tokens	*s_quote_parser(t_tokens *tokens)
{
	t_tokens	*tmp;
	char		*str;

	tmp = tokens;
	tmp = tmp->next;
	str = get_string_s_quote(tmp);
	while (tmp && tmp->token != S_QUOTE)
	{
		tokens = del_token(tokens, tmp);
		if (tokens)
			tmp = tokens->next;
	}
	tokens = del_token(tokens, tmp);
	free(tokens->str);
	tokens->str = str;
	tokens->token = WORD;
	return (tokens);
}
