#include "minishell.h"

t_tokens	*remove_empty_words(t_tokens **tokens)
{
	t_tokens	*tmp;
	t_tokens	*prev;

	tmp = *tokens;
	while (tmp && tmp->token == WORD && ft_strlen(tmp->str) == 0)
	{
		*tokens = tmp->next;
		free(tmp->str);
		free(tmp);
		tmp = *tokens;
	}
	while (tmp)
	{
		if (tmp->token == WORD && ft_strlen(tmp->str) == 0)
		{
			prev->next = tmp->next;
			free(tmp->str);
			free(tmp);
			tmp = prev->next;
			continue ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (*tokens);
}

t_tokens	*remove_sep(t_tokens *tokens)
{
	t_tokens	*tmp;
	t_tokens	*prev;

	tmp = tokens;
	while (tmp && tmp->token == SEP)
	{
		tokens = tmp->next;
		free(tmp->str);
		free(tmp);
		tmp = tokens;
	}
	while (tmp)
	{
		if (tmp->token == SEP)
		{
			prev->next = tmp->next;
			free(tmp->str);
			free(tmp);
			tmp = prev->next;
			continue ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (tokens);
}

t_tokens	*merge_words(t_tokens *tokens)
{
	t_tokens	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->token == WORD && tmp->next && tmp->next->token == WORD)
		{
			tmp->str = ft_strjoin(tmp->str, tmp->next->str);
			del_token(tokens, tmp->next);
			continue ;
		}
		tmp = tmp->next;
	}
	return (tokens);
}

t_tokens	*parser(t_tokens *tokens)
{
	t_tokens	*tmp;
	int			in_d_quote;

	in_d_quote = 0;
	tmp = tokens;
	if (check_close_quote(tokens) == 1)
		return (tokens);
	while (tmp)
	{
		if (tmp->token == S_QUOTE)
			tmp = s_quote_parser(tmp);
		else if (tmp->token == D_QUOTE)
		{
			in_d_quote = !in_d_quote;
			tmp = d_quote_parser(tmp);
		}
		else if (tmp->token == DOLLAR)
		{
			tmp = env_var_parser(tmp, in_d_quote);
			tmp = split_dollar(tmp);
		}
		tmp = tmp->next;
	}
	tokens = merge_words(tokens);
	tokens = remove_sep(tokens);
	if (check_redir(tokens) == 1)
		return (tokens);
	//tokens = remove_empty_words(&tokens);
	return (tokens);
}
