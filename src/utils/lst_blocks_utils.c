#include "minishell.h"

void	lst_clear_redir(t_redir **redir)
{
	t_redir	*tmp;

	if (redir == NULL)
		return ;
	while (*redir)
	{
		tmp = *redir;
		*redir = (*redir)->next;
		if (tmp->file)
			free(tmp->file);
		free(tmp);
	}
}

void	lst_clear_blocks(t_blocks **blocks)
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
		lst_clear_redir(&tmp->redir);
		free(tmp);
	}
}