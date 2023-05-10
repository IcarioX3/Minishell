#include "minishell.h"

int	g_exit_status = 0;

t_blocks	*parsing(t_blocks *blocks, char *input, char **env)
{
	t_tokens	*tokens;

	tokens = NULL;
	tokens = lexer(input, tokens);
	free(input);
	printf("After lexer:\n");
	print_tokens(tokens);
	tokens = parser(tokens, &g_exit_status, env);
	printf("\nAfter parser:\n");
	print_tokens(tokens);
	if (g_exit_status != 0)
		return (lst_clear_token(&tokens), NULL);
	blocks = put_in_blocks(blocks, tokens, &g_exit_status);
	if (!blocks)
	{
		lst_clear_token(&tokens);
		lst_clear_blocks(&blocks);
		return (NULL);
	}
	lst_clear_token(&tokens);
	print_blocks(blocks);
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
		input = readline("\033[36mminishell$\033[0m ");
		add_history(input);
		if (!input || input[0] == '\0')
		{
			free(input);
			if (!input)
				break ;
			continue ;
		}
		blocks = parsing(blocks, input, env);
		if (!blocks)
			continue ;
		if ((check_builtin(blocks->cmd, &envi)) == 1)
			break ;
		lst_clear_blocks(&blocks);
	}
	if (env)
		lst_clear_env(envi);
	printf("Exit status: %d\n", g_exit_status);
	return (0);
}
