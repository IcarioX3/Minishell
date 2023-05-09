#include "minishell.h"

void	lst_clear_redir(t_redir **redir)
{
	t_redir	*tmp;

	if (!redir)
		return ;
	while (*redir)
	{
		tmp = *redir;
		*redir = (*redir)->next;
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
		{
			while (tmp->nb_args > 0)
			{
				if (tmp->cmd[tmp->nb_args - 1] != NULL)
					free(tmp->cmd[tmp->nb_args - 1]);
				tmp->nb_args--;
			}
			free(tmp->cmd);
		}
		lst_clear_redir(&tmp->redir);
		free(tmp);
	}
}
