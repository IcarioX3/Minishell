#include "minishell.h"

int	g_exit_status = 0;

int parsing(t_tokens *tokens, char *input)
{
	tokens = lexer(input, tokens);
	free(input);
	printf("After lexer:\n");
	print_tokens(tokens);
	tokens = parser(tokens, &g_exit_status);
	if (g_exit_status != 0)
	{
		lst_clear_token(&tokens);
		return (1);
	}
	printf("\nAfter parser:\n");
	print_tokens(tokens);
	lst_clear_token(&tokens);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	char		*input;
	t_tokens	*tokens;
	t_blocks	*blocks;

	(void)argv;
	(void)env;
	tokens = NULL;
	blocks = NULL;
	if (argc != 1)
		return (1);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		input = readline("\033[36mminishell$\033[0m ");
		add_history(input);
		if (!input)
		{
			free(input);
			break ;
		}
		if (parsing(tokens, input) == 1)
			continue ;
		blocks = put_in_blocks(blocks, tokens);
		lst_clear_block(&blocks);
	}
	printf("Exit status: %d\n", g_exit_status);
	return (0);
}
