/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_quote_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablevin <ablevin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:04:09 by ablevin           #+#    #+#             */
/*   Updated: 2023/05/20 13:04:10 by ablevin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*empty_string(void)
{
	char	*str;

	str = ft_strdup("");
	return (str);
}

char	*get_string_d_quote(t_tokens *tokens, t_env **env)
{
	char	*str;

	str = NULL;
	if (tokens->token == D_QUOTE)
		return (empty_string());
	while (tokens && tokens->token != D_QUOTE)
	{
		if (tokens->token == DOLLAR)
		{
			if (tokens->next && tokens->next->token == WORD)
			{
				if (ft_strcmp(tokens->next->str, "?") == 1)
					str = ft_strjoin(str, ft_itoa(return_global_exit_status()));
				else
					str = ft_strjoin(str, ft_getenv(tokens->next->str, env));
				tokens = tokens->next;
			}
			else
				str = ft_strjoin(str, tokens->str);
		}
		else
			str = ft_strjoin(str, tokens->str);
		tokens = tokens->next;
	}
	return (str);
}

t_tokens	*d_quote_parser(t_tokens *tokens, t_env **env)
{
	t_tokens	*tmp;
	char		*str;

	tmp = tokens;
	tmp = tmp->next;
	str = get_string_d_quote(tmp, env);
	while (tmp && tmp->token != D_QUOTE)
	{
		tokens = del_token(tokens, tmp);
		tmp = tokens->next;
	}
	tokens = del_token(tokens, tmp);
	free(tokens->str);
	tokens->str = str;
	tokens->token = WORD;
	return (tokens);
}
