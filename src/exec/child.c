#include "minishell.h"

void	exec_first(t_blocks *blocks, t_blocks *tmp, t_env *env)
{
	if (tmp->fd_in != -1)
	{
		if (dup2(tmp->fd_in, STDIN_FILENO) == -1)
			clean_all_exit(blocks, env, errno);
		close(tmp->fd_in);
	}
	if (tmp->fd_out != -1)
	{
		if (dup2(tmp->fd_out, STDOUT_FILENO) == -1)
			clean_all_exit(blocks, env, errno);
		close(tmp->fd_out);
	}
	else
	{
		if (dup2(tmp->pipe[1], STDOUT_FILENO) == -1)
			clean_all_exit(blocks, env, errno);
		close(tmp->pipe[1]);
	}	
}

void	exec_last(t_blocks *blocks, t_blocks *tmp, t_env *env)
{
	if (tmp->fd_in != -1)
	{
		if (dup2(tmp->fd_in, STDIN_FILENO) == -1)
		{
			clean_all_exit(blocks, env, errno);
			close(tmp->fd_in);
		}
	}
	else
	{
		if (dup2(tmp->prev->pipe[0], STDIN_FILENO) == -1)
			clean_all_exit(blocks, env, errno);
		close(tmp->prev->pipe[0]);
	}
	if (tmp->fd_out != -1)
	{
		if (dup2(tmp->fd_out, STDOUT_FILENO) == -1)
			clean_all_exit(blocks, env, errno);
		close(tmp->fd_out);
	}
}

void	exec_middle(t_blocks *blocks, t_blocks *tmp, t_env *env)
{
	if (tmp->fd_in != -1)
	{
		if (dup2(tmp->fd_in, STDIN_FILENO) == -1)
			clean_all_exit(blocks, env, errno);
		close(tmp->fd_in);
	}
	else
	{
		if (dup2(tmp->prev->pipe[0], STDIN_FILENO) == -1)
			clean_all_exit(blocks, env, errno);
		close(tmp->prev->pipe[0]);
	}
	if (tmp->fd_out != -1)
	{
		if (dup2(tmp->fd_out, STDOUT_FILENO) == -1)
			clean_all_exit(blocks, env, errno);
	}
	else
	{
		if (dup2(tmp->pipe[1], STDOUT_FILENO) == -1)
			clean_all_exit(blocks, env, errno);
		close(tmp->pipe[1]);
	}
}

void	exec_one(t_blocks *blocks, t_blocks *tmp, t_env *env)
{
	if (tmp->fd_in != -1)
	{	
		if (dup2(tmp->fd_in, STDIN_FILENO) == -1)
			clean_all_exit(blocks, env, errno);
		close(tmp->fd_in);
	}
	if (tmp->fd_out != -1)
	{
		if (dup2(tmp->fd_out, STDOUT_FILENO) == -1)
			clean_all_exit(blocks, env, errno);
		close(tmp->fd_out);
	}
}

void	child(t_blocks *blocks, t_blocks *tmp, t_env *env)
{
	if (check_before_exec(tmp, env) == 1)
		clean_all_exit(blocks, env, 127);
	if (!tmp->path)
		clean_all_exit(blocks, env, 127);
	if (tmp->prev == NULL && tmp->next == NULL)
		exec_one(blocks, tmp, env);
	else if (tmp->prev == NULL && tmp->next != NULL)
		exec_first(blocks, tmp, env);
	else if (tmp->prev != NULL && tmp->next == NULL)
		exec_last(blocks, tmp, env);
	else if (tmp->next != NULL && tmp->prev != NULL)
		exec_middle(blocks, tmp, env);
	if (is_builtin(tmp->cmd[0]) == 1 && check_builtin(tmp->cmd, &env, &blocks))
		clean_all_exit(blocks, env, 0);
	while (blocks)
	{
		if (blocks->pipe[0] != -1)
			close(blocks->pipe[0]);
		if (blocks->pipe[1] != -1)
			close(blocks->pipe[1]);
		blocks = blocks->next;
	}
	execve(tmp->path, tmp->cmd, tmp->env);
}
