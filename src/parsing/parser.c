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

void	handle_dollar(t_tokens **tokens)
{
	int		in_s_quote;
	int		in_d_quote;
	t_tokens	*tmp;

	in_s_quote = 0;
	in_d_quote = 0;
	tmp = *tokens;
	while (tmp)
	{
		if (tmp->token == S_QUOTE)
			in_s_quote = !in_s_quote;
		if (tmp->token == D_QUOTE)
			in_d_quote = !in_d_quote;
		tmp = tmp->next;
	}
}

void	parser(t_tokens **tokens)
{
	if (check_close_quote(*tokens) == 1)
		return ;
	handle_dollar(tokens);
}
