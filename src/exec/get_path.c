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

void	print_error_path(char *cmd, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

char	**get_path_array(t_env *env, char *cmd)
{
	char	*path;
	char	**path_array;

	path = get_path(env);
	if (!path)
		return (print_error_path(cmd, "No such file or directory"), NULL);
	path_array = ft_split(path, ':');
	free(path);
	if (!path_array)
		return (printf("Error: malloc failed\n"), NULL);
	return (path_array);
}

char	*get_bin_path(char *cmd, t_env *env)
{
	char	*bin_path;
	char	**path_array;
	int		i;

	path_array = get_path_array(env, cmd);
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
	print_error_path(cmd, "command not found");
	free_double_array(path_array);
	return (NULL);
}
