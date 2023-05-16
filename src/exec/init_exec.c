#include "minishell.h"

int	init_pipes(t_blocks *blocks)
{
	t_blocks	*tmp;

	tmp = blocks;
	while (tmp)
	{
		if (pipe(tmp->pipe) == -1)
			return (lst_clear_blocks(&blocks), 1);
		tmp = tmp->next;
	}
	return (0);
}

int	get_nb_cmds(t_blocks *blocks)
{
	int			nb_cmds;
	t_blocks	*tmp;

	nb_cmds = 0;
	tmp = blocks;
	while (tmp)
	{
		nb_cmds++;
		tmp = tmp->next;
	}
	return (nb_cmds);
}

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
			redir->fd = get_fd(redir);
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

int	*init_exec(t_blocks *blocks)
{
	int	*pid;
	int	nb_cmds;

	nb_cmds = get_nb_cmds(blocks);
	if (init_pipes(blocks) == 1)
	{
		global_exit_status(errno);
		return (ft_putstr_fd("minishell: pipe error\n", 2), NULL);
	}
	open_files(blocks);
	pid = malloc(sizeof(int) * nb_cmds);
	if (!pid)
	{
		lst_clear_blocks(&blocks);
		return (ft_putstr_fd("minishell: malloc error\n", 2), NULL);
	}
	return (pid);
}

