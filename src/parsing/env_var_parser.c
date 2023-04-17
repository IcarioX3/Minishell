#include "minishell.h"

t_tokens	*replace_var(t_tokens *token)
{
	free(token->str);
	token->str = ft_strdup(getenv(token->next->str));
	token->token = WORD;
	token = del_token(token, token->next);
	return (token);
}

t_tokens	*env_var_parser(t_tokens *tokens)
{
	t_tokens	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->token == DOLLAR)
		{
			if (tmp->next && tmp->next->token == WORD)
				tmp = replace_var(tmp);
			else
				tmp->token = WORD;
		}
		tmp = tmp->next;
	}
	return (tokens);
}
