#include "minishell.h"

t_tokens	*remove_sep(t_tokens *tokens)
{
	t_tokens	*tmp;

	tmp = tokens;
	while (tmp && tmp->token == SEP)
	{
		tokens = tmp->next;
		free(tmp->str);
		free(tmp);
		tmp = tokens;
	}
	while (tmp && tmp->next)
	{
		if (tmp->next->token == SEP)
			del_token(tokens, tmp->next);
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
		if (tmp->token == DOLLAR)
			tmp->token = WORD;
		tmp = tmp->next;
	}
	return (tokens);
}

int	check_pipe(t_tokens *tokens)
{
	t_tokens	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->token == PIPE)
		{
			if (!tmp->next || tmp->next->token == PIPE || !tmp->previous)
			{
				ft_putstr_fd("minishell:", 2);
				ft_putstr_fd(" syntax error near unexpected token `|'\n", 2);
				return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

t_tokens	*handle_quote(t_tokens *tokens)
{
	int	in_d_quote;

	in_d_quote = 0;
	while (tokens)
	{
		if (tokens->token == S_QUOTE)
			tokens = s_quote_parser(tokens);
		else if (tokens->token == D_QUOTE)
		{
			in_d_quote = !in_d_quote;
			tokens = d_quote_parser(tokens);
		}
		else if (tokens->token == DOLLAR)
		{
			tokens = env_var_parser(tokens, in_d_quote);
			tokens = remove_sep(tokens);
		}
		tokens = tokens->next;
	}
	return (tokens);
}

t_tokens	*parser(t_tokens *tokens, int *g_exit_status)
{
	t_tokens	*tmp;

	tmp = tokens;
	if (check_close_quote(tokens) == 1)
	{
		*g_exit_status = 2;
		return (tokens);
	}
	tokens = handle_quote(tokens);
	tokens = merge_words(tokens);
	tokens = remove_sep(tokens);
	if (check_redir(tokens) == 1 || check_pipe(tokens) == 1)
	{
		*g_exit_status = 2;
		return (tokens);
	}
	tokens = redir_parser(tokens);
	return (tokens);
}
