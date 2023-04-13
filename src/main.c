#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*input;

	(void)argv;
	(void)env;
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
		lexer(input);
		free(input);
	}
	return (0);
}
