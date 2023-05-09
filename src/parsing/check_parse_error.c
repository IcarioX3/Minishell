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

int	check_redir(t_tokens *tokens)
{
	t_tokens	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->token == HEREDOC || tmp->token == APPEND
			|| tmp->token == IN_REDIR || tmp->token == OUT_REDIR)
		{
			if (tmp->next == NULL || tmp->next->token != WORD
				|| (tmp->next->token == WORD && tmp->next->str == NULL))
			{
				ft_putstr_fd("minishell: syntax error: ", 2);
				ft_putstr_fd("near unexpected token `", 2);
				if (tmp->next == NULL)
					ft_putstr_fd("newline", 2);
				else
					ft_putstr_fd(tmp->next->str, 2);
				ft_putstr_fd("'\n", 2);
				return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}
