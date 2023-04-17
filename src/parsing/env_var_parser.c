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
	if (tokens->next && tokens->next->token == WORD)
		tokens = replace_var(tokens);
	else
		tokens->token = WORD;	
	return (tokens);
}
