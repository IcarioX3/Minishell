#include "minishell.h"

char	*get_string_s_quote(t_tokens *tokens)
{
	char	*str;

	str = NULL;
	while (tokens && tokens->token != S_QUOTE)
	{
		str = ft_strjoin(str, tokens->str);
		tokens = tokens->next;
	}
	return (str);
}

t_tokens	*join_s_quote(t_tokens *tokens)
{
	t_tokens	*tmp;
	char		*str;

	tmp = tokens;
	tmp = tmp->next;
	str = get_string_s_quote(tmp);
	while (tmp && tmp->token != S_QUOTE)
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
