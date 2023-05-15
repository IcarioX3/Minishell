#include "minishell.h"

int	get_fd(t_redir *redir)
{
	int	fd;

	fd = -1;
	if (redir->token == IN_REDIR)
		fd = open(redir->file, O_RDONLY);
	else if (redir->token == OUT_REDIR)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->token == APPEND)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (redir->token == HEREDOC)
		fd = redir->pipe_heredoc[0];
}

void	open_files(t_blocks *blocks)
{
	t_blocks	*tmp;
	t_redir		*redir;

	tmp = blocks;
	while (tmp)
	{
		redir = tmp->redir;
		while (redir)
		{
			if (redir->fd == -1)
			{
				ft_putstr_fd("minishell: ", 2);
				perror(redir->file);
				break ;
			}
			redir = redir->next;
		}
		tmp = tmp->next;
	}
}