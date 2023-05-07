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
		tokens = parsing(tokens, input);
		if (g_exit_status != 0)
		{
			lst_clear_token(&tokens);
			continue ;
		}
		blocks = put_in_blocks(blocks, tokens, &g_exit_status);
		lst_clear_token(&tokens);
		print_blocks(blocks);
		lst_clear_blocks(&blocks);
	}
	printf("Exit status: %d\n", g_exit_status);
	return (0);
}
