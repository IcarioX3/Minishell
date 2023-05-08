#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char		*input;
	//t_tokens	*tokens;
	t_env		*envi = NULL;
	char		**ui;

	(void)argv;
	//tokens = NULL;
	if (argc != 1)
		return (1);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	envi = lst_env(env);
	if (!envi)
		return (1);
	while (1)
	{
		input = readline("\033[36mminishell$\033[0m ");
		add_history(input);
		if (!input)
		{
			free(input);
			break ;
		}
		ui = ft_split(input, ' ');
		if ((check_builtin(ui, &envi)) == 1)
			break ;
		free_split(ui);
		//tokens = lexer(input, tokens);
		//printf("After lexer:\n");
		//print_tokens(tokens);
		//free(input);
		//parser(&tokens);
		//printf("\nAfter parser:\n");
		//print_tokens(tokens);
		//lst_clear_token(&tokens);
	}
	if (env)
		lst_clear_env(envi);
	return (0);
}
