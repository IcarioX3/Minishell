#include "minishell.h"

void	print_blocks(t_blocks *blocks)
{
	int	i;

	while (blocks)
	{
		i = 0;
		printf("Command: ");
		while (blocks->cmd[i])
		{
			printf("\"%s\" ", blocks->cmd[i]);
			i++;
		}
		printf("\n");
		printf("Redirections:\n");
		while (blocks->redir)
		{
			printf("File: \"%s\"    ", blocks->redir->file);
			if (blocks->redir->token == IN_REDIR)
				printf("%s", "Type: IN_REDIR\n");
			else if (blocks->redir->token == OUT_REDIR)
				printf("%s", "Type: OUT_REDIR\n");
			else if (blocks->redir->token == HEREDOC)
				printf("%s", "Type: HEREDOC\n");
			else if (blocks->redir->token == APPEND)
				printf("%s", "Type: APPEND\n");
			blocks->redir = blocks->redir->next;
		}
		printf("\n");
		blocks = blocks->next;
	}
}