#include "minishell.h"

void	lst_clear_env(t_env *envi)
{
	t_env	*tmp;

	if (envi == NULL)
		return ;
	while (envi)
	{
		tmp = envi;
		envi = (envi)->next;
		if (tmp->str)
			free(tmp->str);
		free(tmp);
	}
	envi = NULL;
}

t_env	*ft_lstlast_env(t_env *env)
{
	while (env)
	{
		if (env->next == NULL)
			return (env);
		env = env->next;
	}
	return (NULL);
}

t_env	*ft_lstadd_back_env(t_env *env, t_env *new)
{
	t_env	*tmp;

	if (env == NULL)
	{
		env = new;
	}
	else
	{
		tmp = ft_lstlast_env(env);
		tmp->next = new;
		new->prev = tmp;
	}
	return (env);
}

t_env	*lst_new_env(t_env *envi, char *str)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	new->str = ft_strdup(str);
	new->next = NULL;
	new->prev = NULL;
	envi = ft_lstadd_back_env(envi, new);
	return (envi);
}

t_env	*lst_new_env_null(t_env *envi, char *str)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	new->str = ft_strdup(str);
	new->next = NULL;
	new->prev = NULL;
	envi = ft_lstadd_back_env(envi, new);
	return (envi);
}

t_env *lst_env(char **env)
{
    t_env *envi;

    int i = 1;
	envi = NULL;
	char	cwd[1024];
    while (*env && env[i])
    {
        envi = lst_new_env(envi, env[i]);
        i++;
    }
	if (*env == NULL)
	{
		envi = lst_new_env_null(envi, getcwd(cwd, sizeof(cwd)));
		envi = lst_new_env_null(envi, "SHLVL=1");
		envi = lst_new_env_null(envi, "_=/usr/bin/env");
	}
    return (envi);
}