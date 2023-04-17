#include "minishell.h"

char	*get_string_d_quote(t_tokens *tokens)
{
	char	*str;

	str = NULL;
	while (tokens && tokens->token != D_QUOTE)
	{
		if (tokens->token == DOLLAR)
		{
			if (tokens->next && tokens->next->token == WORD)
			{
				str = ft_strjoin(str, getenv(tokens->next->str));
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

t_tokens	*d_quote_parser(t_tokens *tokens)
{
	t_tokens	*tmp;
	char		*str;

	tmp = tokens;
	tmp = tmp->next;
	str = get_string_d_quote(tmp);
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
