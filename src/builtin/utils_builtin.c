#include "minishell.h"

void	lst_clear_env(t_env **envi)
{
	t_env	*tmp;

	if (envi == NULL)
		return ;
	while (*envi)
	{
		tmp = *envi;
		*envi = (*envi)->next;
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

void	ft_lstadd_back_env(t_env **env, t_env *new)
{
	t_env	*tmp;

	if (*env == NULL)
	{
		*env = new;
	}
	else
	{
		tmp = ft_lstlast_env(*env);
		tmp->next = new;
		new->prev = tmp;
	}
}


t_env	*lst_new_env(t_env *envi, char *str)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	new->str = ft_strdup(str);
	new->next = NULL;
	new->prev = NULL;
	if (envi == NULL)
		envi = new;
	else
		ft_lstadd_back_env(&envi, new);
	return (envi);
}

t_env	*lst_env(t_env *envi, char **env)
{
	int i;

	i = 0;
	while (env[i] != NULL)
	{
		envi = lst_new_env(envi, env[i]);
		i++;
	}
	return (envi);
}