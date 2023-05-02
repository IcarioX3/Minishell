#include "minishell.h"

void	print_blocks(t_blocks *blocks)
{
	while (blocks)
	{
		printf("Cmd count = %d\n", blocks->cmd_count);
		while (blocks->cmd_count--)
			printf("Cmd: \"%s\"\n", blocks->cmd[blocks->cmd_count]);
		printf("Heredoc count = %d\n", blocks->heredoc_count);
		while (blocks->heredoc_count--)
			printf("Heredoc: \"%s\"\n", blocks->heredoc[blocks->heredoc_count]);
		printf("In count = %d\n", blocks->in_count);
		while (blocks->in_count--)
			printf("In: \"%s\"\n", blocks->in[blocks->in_count]);
		printf("Out count = %d\n", blocks->out_count);
		while (blocks->out_count--)
			printf("Out: \"%s\"\n", blocks->out[blocks->out_count]);
		printf("Append count = %d\n", blocks->append_count);
		while (blocks->append_count--)
			printf("Append: \"%s\"\n", blocks->append[blocks->append_count]);
		blocks = blocks->next;
	}
}
