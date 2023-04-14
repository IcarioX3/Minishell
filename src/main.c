#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char		*input;
	t_tokens	*tokens;

	(void)argv;
	(void)env;
	tokens = NULL;
	if (argc != 1)
		return (1);
	while (1)
	{
		input = readline("\033[36mminishell$\033[0m ");
		add_history(input);
		if (input[0] == '0')
		{
			free(input);
			break ;
		}
		tokens = lexer(input, tokens);
		printf("After lexer:\n");
		print_tokens(tokens);
		free(input);
		parser(&tokens);
		printf("\nAfter parser:\n");
		print_tokens(tokens);
		lst_clear_token(&tokens);
	}
	return (0);
}
