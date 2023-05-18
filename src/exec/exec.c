#include "minishell.h"

char	**env_to_array(t_env *env)
{
	char	**env_array;
	int		i;
	int		len;
	t_env	*tmp;

	tmp = env;
	len = 0;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	env_array = malloc(sizeof(char *) * (len + 1));
	if (!env_array)
		return (NULL);
	i = 0;
	while (env)
	{
		env_array[i] = ft_strdup(env->str);
		if (!env_array[i])
			return (free_double_array(env_array), NULL);
		env = env->next;
		i++;
	}
	return (env_array[i] = NULL, env_array);
}

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

int	exec(t_blocks *blocks, t_env *env)
{
	t_blocks	*tmp;

	tmp = blocks;
	blocks->pid = init_exec(blocks);
	blocks->env = env_to_array(env);
	if (!blocks->pid || !blocks->env)
	{
		return (lst_clear_blocks(&blocks), 1);
	}	
	if (!blocks->next && is_builtin(blocks->cmd[0]))
	{
		if (check_builtin(blocks->cmd, &env, &blocks) == 1)
			return (1);
		return (0);
	}
	core(tmp, env);
	parent(blocks);
	return (0);
}
