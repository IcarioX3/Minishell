#include "minishell.h"

char	*get_path(t_env *env)
{
	char	*path;
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->str, "PATH=", 5))
		{
			path = ft_strdup(tmp->str + 5);
			if (!path)
				return (NULL);
			return (path);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	*get_bin_path(char *cmd, t_env *env)
{
	char	*bin_path;
	char	*path;
	char	**path_array;
	int		i;

	path = get_path(env);
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (NULL);
	}
	path_array = ft_split(path, ':');
	free(path);
	if (!path_array)
		return (NULL);
	i = 0;
	while (path_array[i] && cmd[0] != '\0')
	{
		bin_path = ft_strjoin(ft_strdup(path_array[i]), "/");
		if (!bin_path)
			return (free_double_array(path_array), NULL);
		bin_path = ft_strjoin(bin_path, cmd);
		if (!bin_path)
			return (free_double_array(path_array), NULL);
		if (access(bin_path, F_OK | X_OK) == 0)
			return (free_double_array(path_array), bin_path);
		free(bin_path);
		i++;
	}
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	free_double_array(path_array);
	return (NULL);
}
