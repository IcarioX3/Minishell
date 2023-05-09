#include "minishell.h"

int	g_exit_status = 0;

t_tokens	*parsing(t_tokens *tokens, char *input)
{
	tokens = lexer(input, tokens);
	free(input);
	printf("After lexer:\n");
	print_tokens(tokens);
	tokens = parser(tokens, &g_exit_status);
	printf("\nAfter parser:\n");
	print_tokens(tokens);
	return (tokens);
}

int	main(int argc, char **argv, char **env)
{
	char		*input;

	t_tokens	*tokens;
	t_blocks	*blocks;

	(void)argv;
	tokens = NULL;
	blocks = NULL;
  t_env		*envi = NULL;

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
		if (input[0] == '\0')
		{
			free(input);
			continue ;
		}
		tokens = parsing(tokens, input);
		if (g_exit_status != 0)
		{
			lst_clear_token(&tokens);
			continue ;
		}
		blocks = put_in_blocks(blocks, tokens, &g_exit_status);
		if (!blocks)
		{
			lst_clear_token(&tokens);
			continue ;
		}
		lst_clear_token(&tokens);
		print_blocks(blocks);
    if ((check_builtin(blocks->cmd, &envi)) == 1)
			break ;
		lst_clear_blocks(&blocks);
	}
	if (env)
		lst_clear_env(envi);
	printf("Exit status: %d\n", g_exit_status);
	return (0);
}
