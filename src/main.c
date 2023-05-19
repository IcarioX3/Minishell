#include "minishell.h"

t_blocks	*parsing(t_blocks *blocks, char *input, t_env **env)
{
	t_tokens	*tokens;

	tokens = NULL;
	tokens = lexer(input, tokens);
	free(input);
	//printf("After lexer:\n");
	//print_tokens(tokens);
	tokens = parser(tokens, env);
	//printf("After parser:\n");
	//print_tokens(tokens);
	if (return_global_exit_status() != 0)
		return (lst_clear_token(&tokens), NULL);
	blocks = put_in_blocks(blocks, tokens);
	if (!blocks)
	{
		lst_clear_token(&tokens);
		lst_clear_blocks(&blocks);
		return (NULL);
	}
	lst_clear_token(&tokens);
	//print_blocks(blocks);
	return (blocks);
}

int	main(int argc, char **argv, char **env)
{
	char		*input;
	t_blocks	*blocks;
	t_env		*envi;

	(void)argv;
	envi = NULL;
	blocks = NULL;
	if (argc != 1)
		return (1);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	envi = lst_env(env);
	if (!envi)
		return (1);
	while (1)
	{
		printf("Exit status: %d\n", return_global_exit_status());
		input = readline("\033[36mminishell$\033[0m ");
		add_history(input);
		if (!input || input[0] == '\0')
		{
			free(input);
			if (!input)
			{
				printf("exit\n");
				break ;
			}
			continue ;
		}
		blocks = parsing(blocks, input, &envi);
		if (!blocks)
			continue ;
/* 		if ((check_builtin(blocks->cmd, &envi, &blocks)) == 1)
			break ; */
		if (exec(blocks, envi) == 1)
			break ;
		//heredoc(blocks, &g_exit_status);
		lst_clear_blocks(&blocks);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handle_sigint);
	}
	if (envi)
		lst_clear_env(envi);
	return (0);
}
