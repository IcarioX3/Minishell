#include "minishell.h"

int	is_last_out(t_redir *redir)
{
	t_redir	*tmp;

	tmp = redir;
	while (tmp)
	{
		if (tmp->token == OUT_REDIR || tmp->token == APPEND)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	is_last_in(t_redir *redir)
{
	t_redir	*tmp;

	tmp = redir;
	while (tmp)
	{
		if (tmp->token == IN_REDIR)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

/* int	get_fd(t_redir *redir, t_blocks *blocks)
{
	int	fd;

	fd = -2;
	if (redir->token == IN_REDIR)
	{
		fd = open(redir->file, O_RDONLY);
		if (fd != -1 && is_last_in(redir->next))
			blocks->fd_in = fd;
	}
	else if (redir->token == OUT_REDIR)
	{
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd != -1 && is_last_out(redir->next))
			blocks->fd_out = fd;
	}
	else if (redir->token == APPEND)
	{
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd != -1 && is_last_out(redir->next))
			blocks->fd_out = fd;
	}
	else if (redir->token == HEREDOC)
	{
		if (is_last_in(redir->next))
			blocks->fd_in = redir->pipe_heredoc[0];
		else
			close(redir->pipe_heredoc[0]);
		fd = redir->pipe_heredoc[0];
	}
	return (fd);
} */

int	get_fd_out(t_redir *redir, t_blocks *blocks)
{
	int	fd;

	fd = -2;
	if (redir->token == OUT_REDIR)
	{
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd != -1 && is_last_out(redir->next))
			blocks->fd_out = fd;
	}
	else if (redir->token == APPEND)
	{
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd != -1 && is_last_out(redir->next))
			blocks->fd_out = fd;
	}
	return (fd);
}

int	get_fd(t_redir *redir, t_blocks *blocks)
{
	int	fd;

	fd = -2;
	if (redir->token == IN_REDIR)
	{
		fd = open(redir->file, O_RDONLY);
		if (fd == -1)
			return (-1);
		if (is_last_in(redir->next))
			blocks->fd_in = fd;
	}
	else if (redir->token == OUT_REDIR || redir->token == APPEND)
	{
		if (get_fd_out(redir, blocks) == -1)
			return (-1);
	}
	else if (redir->token == HEREDOC)
	{
		if (is_last_in(redir->next))
			blocks->fd_in = redir->pipe_heredoc[0];
		fd = redir->pipe_heredoc[0];
	}
	return (fd);
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
			redir->fd = get_fd(redir, tmp);
			if (redir->fd == -1)
			{
				global_exit_status(errno);
				ft_putstr_fd("minishell: ", 2);
				perror(redir->file);
				break ;
			}
			redir = redir->next;
		}
		tmp = tmp->next;
	}
}
