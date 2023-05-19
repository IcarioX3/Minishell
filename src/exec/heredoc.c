#include "minishell.h"

void	child_heredoc(t_blocks *blocks, t_redir *redir, t_env *env)
{
	char	*line;

	line = NULL;
	signal(SIGINT, signal_heredoc);
	close(redir->pipe_heredoc[0]);
	while (return_global_exit_status() == 0)
	{
		ft_putstr_fd("> ", STDIN_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (!line)
		{
			free(line);
			clean_all_exit(blocks, env, 1);
		}
		if (ft_strncmp(line, redir->file, ft_strlen(redir->file)) == 0)
		{
			free(line);
			clean_all_exit(blocks, env, 0);
		}
		ft_putstr_fd(line, redir->pipe_heredoc[1]);
		free(line);
	}
	clean_all_exit(blocks, env, 1);
}

void	parent_heredoc(t_redir *redir, int pid)
{
	int	status;

	close(redir->pipe_heredoc[1]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		global_exit_status(WEXITSTATUS(status));
}

void	error_fork_heredoc(t_blocks *blocks, t_env *env)
{
	clean_all_exit(blocks, env, 1);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	exit(errno);
}

void	do_heredoc(t_blocks *blocks, t_redir *redir, t_env *env, int pid)
{
	if (pipe(redir->pipe_heredoc) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		clean_all_exit(blocks, env, 1);
	}
	pid = fork();
	if (pid == -1)
		error_fork_heredoc(blocks, env);
	if (pid == 0)
		child_heredoc(blocks, redir, env);
	else
		parent_heredoc(redir, pid);
}

int	heredoc(t_blocks *blocks, t_env *env)
{
	t_blocks	*tmp;
	t_redir		*tmp_redir;
	int			pid;

	pid = 0;
	tmp = blocks;
	while (tmp)
	{
		tmp_redir = tmp->redir;
		while (tmp_redir)
		{
			if (tmp_redir->token == HEREDOC)
				do_heredoc(blocks, tmp_redir, env, pid);
			tmp_redir = tmp_redir->next;
		}
		tmp = tmp->next;
	}
	return (1);
}
