/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablevin <ablevin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:04:11 by ablevin           #+#    #+#             */
/*   Updated: 2023/05/20 13:04:12 by ablevin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*replace_exit(t_tokens *token)
{
	free(token->str);
	token->str = ft_itoa(return_global_exit_status());
	token = del_token(token, token->next);
	return (token);
}

t_tokens	*replace_var(t_tokens *token, int in_quote, t_env **env)
{
	free(token->str);
	token->str = ft_strdup(ft_getenv(token->next->str, env));
	if (in_quote == 0)
		token->token = DOLLAR;
	else
		token->token = WORD;
	token = del_token(token, token->next);
	return (token);
}

t_tokens	*env_var_parser(t_tokens *tokens, int in_quote, t_env **env)
{
	if (tokens->next && tokens->next->token == WORD)
	{
		if (tokens->next && ft_strncmp(tokens->next->str, "?", 2) == 0)
			tokens = replace_exit(tokens);
		else
			tokens = replace_var(tokens, in_quote, env);
	}
	else
		tokens->token = WORD;
	return (tokens);
}
