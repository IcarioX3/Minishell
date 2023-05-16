#include "minishell.h"

char	**env_to_array(t_env *env)
{
	char	**env_array;
	int		i;
	int	len;
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
	}
	env_array[i] = NULL;
	return (env_array);
}

void	check_before_exec(t_blocks *blocks, t_env *env, int *pid, char **envi)
{
	 t_redir	*tmp;

	tmp = blocks->redir;
	while (tmp)
	{
		if (tmp->fd == -1)
		{
			free(pid);
			free_double_array(envi);
			clean_all(blocks, env);
			exit(errno);
		}
		tmp = tmp->next;
	}
	if (access(blocks->cmd[0], F_OK | X_OK) == 0)
		blocks->path = ft_strdup(blocks->cmd[0]);
	else
		blocks->path = get_bin_path(blocks->cmd[0], env);
}

int	exec(t_blocks *blocks, t_env *env)
{
	int	*pid;
	int	i;
	t_blocks	*tmp;
	char	**env_array;
	int		status;
	int		nb_cmd;

	tmp = blocks;
	pid = init_exec(blocks);
	env_array = env_to_array(env);
	if (!pid || !env_array)
		return (lst_clear_blocks(&blocks), 1);
	i = 0;
	while (tmp)
	{
		check_before_exec(tmp, env, pid, env_array);
		if (!tmp->path)
		{
			free(pid);
			free_double_array(env_array);
			clean_all(blocks, env);
			return (1);
		}
		if (pid[i] == 0)
		{
			execve(tmp->path, tmp->cmd, env_array);
		}
		tmp = tmp->next;
		i++;
	}
	nb_cmd = get_nb_cmds(blocks);
	i = 0;
	while (i < nb_cmd)
	{
		waitpid(pid[i], &status, 0);
		if (WIFEXITED(status))
			global_exit_status(WEXITSTATUS(status));
		i++;
	}
	free(pid);
	free_double_array(env_array);
	lst_clear_blocks(&blocks);
	return (0);
}
