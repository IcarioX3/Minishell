#include "minishell.h"

void	print_tokens(t_tokens *tokens)
{
	while (tokens)
	{
		printf("\"%s\"    ", tokens->str);
		if (tokens->token == PIPE)
			printf("%s", "Token: PIPE\n");
		else if (tokens->token == DOLLAR)
			printf("%s", "Token: DOLLAR\n");
		else if (tokens->token == S_QUOTE)
			printf("%s", "Token: S_QUOTE\n");
		else if (tokens->token == D_QUOTE)
			printf("%s", "Token: D_QUOTE\n");
		else if (tokens->token == IN_REDIR)
			printf("%s", "Token: IN_REDIR\n");
		else if (tokens->token == OUT_REDIR)
			printf("%s", "Token: OUT_REDIR\n");
		else if (tokens->token == HEREDOC)
			printf("%s", "Token: HEREDOC\n");
		else if (tokens->token == APPEND)
			printf("%s", "Token: APPEND\n");
		else if (tokens->token == SEP)
			printf("%s", "Token: SEP\n");
		else if (tokens->token == WORD)
			printf("%s", "Token: WORD\n");
		tokens = tokens->next;
	}
}
