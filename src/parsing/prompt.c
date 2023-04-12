#include "minishell.h"

void	prompt(void)
{
	char	*input;

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
}
