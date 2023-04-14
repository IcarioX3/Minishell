#include "minishell.h"

int	check_close_quote(t_tokens *tokens)
{
	int	s_quote;
	int	d_quote;

	s_quote = 0;
	d_quote = 0;
	while (tokens)
	{
		if (tokens->token == S_QUOTE)
			s_quote++;
		if (tokens->token == D_QUOTE)
			d_quote++;
		tokens = tokens->next;
	}
	if (s_quote % 2 != 0)
		return (print_error("Unmatched single quote"), 1);
	if (d_quote % 2 != 0)
		return (print_error("Unmatched double quote"), 1);
	return (0);
}

void	parser(t_tokens **tokens)
{
	t_tokens	*tmp;

	tmp = *tokens;
	if (check_close_quote(*tokens) == 1)
		return ;
	while (tmp)
	{
		if (tmp->token == S_QUOTE)
			tmp = join_s_quote(tmp);
		tmp = tmp->next;
	}
}
