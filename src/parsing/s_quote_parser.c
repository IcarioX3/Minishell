#include "minishell.h"

/* t_tokens	*join_s_quote(t_tokens *tokens)
{
	t_tokens	*tmp;
	char		*str;

	tmp = tokens;
	str = NULL;
	tmp = tmp->next;
	while (tmp && tmp->token != S_QUOTE)
	{
		str = ft_strjoin(str, tmp->str);
		tokens->next = tmp->next;
		tmp->next->previous = tokens;
		free(tmp->str);
		free(tmp);
		tmp = tokens->next;
	}
	if (tmp->token == S_QUOTE)
	{
		tokens->next = tmp->next;
		if (tmp->next)
			tmp->next->previous = tokens;
		free(tmp->str);
		free(tmp);
	}
	printf("str = %s\n", str);
	free(tokens->str);
	tokens->str = str;
	tokens->token = WORD;
	return (tokens);
} */
