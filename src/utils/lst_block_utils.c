#include "minishell.h"

void	lst_clear_block(t_blocks **blocks)
{
	t_blocks	*tmp;

	if (blocks == NULL)
		return ;
	while (*blocks)
	{
		tmp = *blocks;
		*blocks = (*blocks)->next;
		if (tmp->cmd)
			free_double_array(tmp->cmd);
		if (tmp->heredoc)
			free_double_array(tmp->heredoc);
		if (tmp->in)
			free_double_array(tmp->in);
		if (tmp->out)
			free_double_array(tmp->out);
		if (tmp->append)
			free_double_array(tmp->append);
		free(tmp);
	}
}
