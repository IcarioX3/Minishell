#include "minishell.h"

t_tokens	*replace_var(t_tokens *token, int in_quote, t_env **env)
{
	free(token->str);
	token->str = ft_strdup(ft_getenv(token->next->str, env));
	if (in_quote == 0)
		token->token = DOLLAR;
	else
		token->token = WORD;
	token = del_token(token, token->next);
	return (token);
}

t_tokens	*env_var_parser(t_tokens *tokens, int in_quote, t_env **env)
{
	if (tokens->next && tokens->next->token == WORD)
		tokens = replace_var(tokens, in_quote, env);
	else
		tokens->token = WORD;
	return (tokens);
}
