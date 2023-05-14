#include "minishell.h"

int	ft_home(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while(tmp)
	{
		if (ft_strnstr(tmp->str, "HOME", 4) != NULL)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	ft_old_pwd(t_env **env, char *true_pwd, char *true_old)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strnstr(tmp->str, "PWD", 3) != NULL)
		{
			free(tmp->str);
			tmp->str = ft_strdup(true_pwd);
			if (!tmp->str)
				return (1);
		}
		if (ft_strnstr(tmp->str, "OLDPWD", 3) != NULL)
		{
			free(tmp->str);
			tmp->str = ft_strdup(true_old);
			if (!tmp->str)
				return (1);
		}

		tmp = tmp->next;
	}
	return (0);
}

int	ft_check_pwd(t_env **env, char **true_env)
{
	int i = 0;
	int j = 0;
	while(true_env[i])
	{
		if (ft_strnstr(true_env[i], "PWD", 3) != NULL)
		{
			while (true_env[j])
			{
				if (ft_strnstr(true_env[j], "OLDPWD", 6) != NULL)
				{
					if (ft_old_pwd(env, true_env[i], true_env[j]) == 1)
						return (1);
					return (0);
				}
				j++;
			}
		}
		i++;
	}
	return (0);
}

int	ft_cd(t_env **env, char **input, int *g_exit_status, char **true_env)
{
	if (ft_strlen(input[0]) == 2)
	{
		if (ft_strnstr(input[0], "cd", 2) != NULL)
		{
			if (input[1] == NULL && ft_home(env) == 0)
				chdir("/");
			else
			{
				if (chdir(input[1]) != 0)
				{
					*g_exit_status = 1;
					perror("cd");
				}
			}
			if (ft_check_pwd(env, true_env) == 1)
				return (1);
		}
	}
	return (0);
}
