#include "minishell.h"

int	check_close_quote(t_tokens *tokens)
{
	int	s_quote;
	int	d_quote;

	s_quote = 0;
	d_quote = 0;
	while (tokens)
	{
		if (tokens->token == S_QUOTE && d_quote == 0)
			s_quote = !s_quote;
		else if (tokens->token == D_QUOTE && s_quote == 0)
			d_quote = !d_quote;
		tokens = tokens->next;
	}
	if (s_quote == 1 || d_quote == 1)
	{
		ft_putstr_fd("minishell: syntax error: ", 2);
		ft_putstr_fd("unterminated quote\n", 2);
		return (1);
	}
	return (0);
}

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
			tmp = env_var_parser(tmp, in_d_quote);
		if (tmp->token == DOLLAR)
			tmp = split_dollar(tmp);
		tmp = tmp->next;
	}
	tokens = remove_empty_words(&tokens);
	tokens = remove_sep(tokens);
	return (tokens);
}
