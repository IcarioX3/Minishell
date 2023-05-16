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
		if (tmp)
			free(tmp->file);
		if (tmp->fd != -1 && tmp->fd != -2)
			close(tmp->fd);
		free(tmp);
	}
}

void	close_pipes(t_blocks *blocks)
{
	t_blocks	*tmp;

	tmp = blocks;
	while (tmp)
	{
		if (tmp->pipe[0] != -1)
			close(tmp->pipe[0]);
		if (tmp->pipe[1] != -1)
			close(tmp->pipe[1]);
		tmp = tmp->next;
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
		close_pipes(tmp);
		lst_clear_redir(&tmp->redir);
		free(tmp->path);
		free(tmp);
	}
}
