#include "minishell.h"

void	error_fork(t_blocks *blocks, t_env *env)
{
	clean_all(blocks, env);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	exit(errno);
}

void	core(t_blocks *blocks, t_env *env)
{
	t_blocks	*tmp;
	int			i;

	i = 0;
	tmp = blocks;
	while (tmp)
	{
		signal(SIGQUIT, signal_fork);
		signal(SIGINT, signal_fork);
		blocks->pid[i] = fork();
		if (blocks->pid[i] == -1)
			error_fork(blocks, env);
		if (blocks->pid[i] == 0)
			child(blocks, tmp, env);
		if (tmp->next)
			close(tmp->pipe[1]);
		if (tmp->prev)
			close(tmp->prev->pipe[0]);
		tmp = tmp->next;
		i++;
	}
}

void	parent(t_blocks *blocks)
{
	int	nb_cmd;
	int	i;
	int	status;

	nb_cmd = get_nb_cmds(blocks);
	i = 0;
	while (i < nb_cmd)
	{
		waitpid(blocks->pid[i], &status, 0);
		if (WIFEXITED(status))
			global_exit_status(WEXITSTATUS(status));
		i++;
	}
}

int	one_builtin(t_blocks *blocks, t_env *env)
{
	int	stdout_copy;

	stdout_copy = dup(STDOUT_FILENO);
	if (stdout_copy == -1)
		return (1);
	if (blocks->fd_out != -1 && blocks->fd_out != -2)
	{
		if (dup2(blocks->fd_out, STDOUT_FILENO) == -1)
			return (1);
		close(blocks->fd_out);
	}
	if (check_builtin(blocks->cmd, &env, &blocks) == 1)
		return (1);
	if (dup2(stdout_copy, STDOUT_FILENO) == -1)
		return (1);
	close(stdout_copy);
	return (0);
}

int	exec(t_blocks *blocks, t_env *env)
{
	t_blocks	*tmp;

	tmp = blocks;
	blocks->pid = init_exec(blocks, env);
	blocks->env = env_to_array(env);
	if (!blocks->pid || !blocks->env)
	{
		return (lst_clear_blocks(&blocks), 1);
	}	
	if (!blocks->next && is_builtin(blocks->cmd[0]))
	{
		if (one_builtin(blocks, env) == 1)
			return (1);
		return (0);
	}
	core(tmp, env);
	parent(blocks);
	return (0);
}
