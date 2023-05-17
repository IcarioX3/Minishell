#include "minishell.h"

int	ft_join_old(t_env **old)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strdup("OLD");
	if (!tmp)
		return (1);
	tmp2 = ft_strjoin(tmp, (*old)->str);
	if (!tmp2)
	{
		free(tmp);
		return (1);
	}
	free((*old)->str);
	(*old)->str = ft_strdup(tmp2);
	if (!(*old)->str)
	{
		free(tmp2);
		return (1);
	}
	free(tmp2);
	return (0);
}

int	ft_join_pwd(t_env **pwd)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strdup("PWD=");
	if (!tmp)
		return (1);
	tmp2 = ft_strjoin(tmp, (*pwd)->str);
	if (!tmp2)
	{
		free(tmp);
		return (1);
	}
	free((*pwd)->str);
	(*pwd)->str = ft_strdup(tmp2);
	if (!(*pwd)->str)
	{
		free(tmp2);
		return (1);
	}
	free(tmp2);
	return (0);
}

int	ft_old_pwd(t_env **true_old, t_env **true_pwd)
{
	t_env	*tmp;
	t_env	*tmp2;
	char	cwd[4096];

	tmp = *true_old;
	tmp2 = *true_pwd;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("Erreur lors de l'appel à getcwd()");
		return (1);
	}
	free(tmp->str);
	tmp->str = ft_strdup(tmp2->str);
	if (!tmp->str)
		return (1);
	free(tmp2->str);
	tmp2->str = ft_strdup(cwd);
	if (!tmp2->str)
		return (1);
	if (ft_join_old(true_old) == 1)
		return (1);
	if (ft_join_pwd(true_pwd) == 1)
		return (1);
	return (0);
}

int	ft_check_pwd(t_env **env)
{
	t_env	*tmp;
	t_env	*tmp2;

	tmp = *env;
	tmp2 = *env;
	while (tmp)
	{
		if (ft_strnstr(tmp->str, "PWD", 3) != NULL)
		{
			while (tmp2)
			{
				if (ft_strnstr(tmp2->str, "OLDPWD", 6) != NULL)
				{
					if (ft_old_pwd(&tmp2, &tmp) == 1)
						return (1);
					return (0);
				}
				tmp2 = tmp2->next;
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

int	ft_cd(t_env **env, char **input)
{
	if (ft_strlen(input[0]) == 2)
	{
		if (ft_strnstr(input[0], "cd", 2) != NULL)
		{
			if (ft_home(env) == 1 && input[1] == NULL)
			{
				global_exit_status(1);
				ft_putstr_fd("cd: HOME not set\n", 2);
				return (2);
			}
			if (input[1] == NULL)
				chdir("/");
			else
			{
				if (chdir(input[1]) == -1)
				{
					global_exit_status(1);
					perror("cd");
				}
			}
			if (ft_check_pwd(env) == 1)
				return (1);
		}
	}
	return (0);
}
