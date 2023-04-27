#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char		*input;
	t_tokens	*tokens;
	t_env		*envi = NULL;
	char		**ui;

	(void)argv;
	tokens = NULL;
	if (argc != 1)
		return (1);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	envi = lst_env(env);
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
		check_builtin(ui, envi);
		tokens = lexer(input, tokens);
		//printf("After lexer:\n");
		//print_tokens(tokens);
		free(input);
		parser(&tokens);
		//printf("\nAfter parser:\n");
		//print_tokens(tokens);
		lst_clear_token(&tokens);
	}
	lst_clear_env(envi);
	free_split(ui);
	return (0);
}
