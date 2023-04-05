#include "minishell.h"

void	prompt(void)
{
	char	*input;
	
	while (1)
	{
		input = readline("$ ");
		printf("%s\n", input);
		if (input[0] == '0')
			break ;
	}
}
