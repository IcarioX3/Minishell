/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablevin <ablevin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:04:15 by ablevin           #+#    #+#             */
/*   Updated: 2023/05/20 13:04:16 by ablevin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*special_token(t_tokens *tokens, char *str, int i)
{
	if (str[i] == '|')
		tokens = lst_new_token(tokens, ft_substr(str, i, 1), PIPE);
	else if (str[i] == '$')
		tokens = lst_new_token(tokens, ft_substr(str, i, 1), DOLLAR);
	else if (str[i] == '\'')
		tokens = lst_new_token(tokens, ft_substr(str, i, 1), S_QUOTE);
	else if (str[i] == '\"')
		tokens = lst_new_token(tokens, ft_substr(str, i, 1), D_QUOTE);
	return (tokens);
}

t_tokens	*redir_token(t_tokens *tokens, char *str, int *i)
{
	if (str[*i] == '<')
	{
		if (str[*i + 1] == '<')
		{
			tokens = lst_new_token(tokens, ft_substr(str, *i, 2), HEREDOC);
			(*i)++;
		}
		else
			tokens = lst_new_token(tokens, ft_substr(str, *i, 1), IN_REDIR);
	}
	else if (str[*i] == '>')
	{
		if (str[*i + 1] == '>')
		{
			tokens = lst_new_token(tokens, ft_substr(str, *i, 2), APPEND);
			(*i)++;
		}
		else
			tokens = lst_new_token(tokens, ft_substr(str, *i, 1), OUT_REDIR);
	}
	return (tokens);
}

t_tokens	*whitespace_token(t_tokens *tokens, char *str, int *i)
{
	int	j;

	j = *i;
	while (is_whitespace(str[j]))
		j++;
	tokens = lst_new_token(tokens, ft_substr(str, *i, j - *i), SEP);
	*i = j - 1;
	return (tokens);
}

t_tokens	*word_token(t_tokens *tokens, char *str, int *i)
{
	int	j;

	j = *i;
	while (str[j] && !is_whitespace(str[j]) && !is_special(str[j]))
		j++;
	tokens = lst_new_token(tokens, ft_substr(str, *i, j - *i), WORD);
	*i = j - 1;
	return (tokens);
}

t_tokens	*lexer(char *str, t_tokens *tokens)
{
	int			i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|' || str[i] == '$' || str[i] == '\'' || str[i] == '\"')
			tokens = special_token(tokens, str, i);
		else if (str[i] == '<' || str[i] == '>')
			tokens = redir_token(tokens, str, &i);
		else if (is_whitespace(str[i]))
			tokens = whitespace_token(tokens, str, &i);
		else
			tokens = word_token(tokens, str, &i);
		i++;
	}
	return (tokens);
}
