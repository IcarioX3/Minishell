#include "minishell.h"

t_tokens	*replace_var(t_tokens *token, int in_quote)
{
	free(token->str);
	token->str = ft_strdup(getenv(token->next->str));
	if (in_quote == 0)
		token->token = DOLLAR;
	else
		token->token = WORD;
	token = del_token(token, token->next);
	return (token);
}

t_tokens	*env_var_parser(t_tokens *tokens, int in_quote)
{
	if (tokens->next && tokens->next->token == WORD)
		tokens = replace_var(tokens, in_quote);
	else
		tokens->token = WORD;
	return (tokens);
}
