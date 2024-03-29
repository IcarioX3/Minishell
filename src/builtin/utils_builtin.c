/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablevin <ablevin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:03:34 by ablevin           #+#    #+#             */
/*   Updated: 2023/05/20 13:03:35 by ablevin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		tmp->str = NULL;
		free(tmp);
		tmp = NULL;
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
	if (!new)
		return (NULL);
	new->str = ft_strdup(str);
	if (!new->str)
	{
		free(new);
		return (NULL);
	}
	new->next = NULL;
	new->prev = NULL;
	envi = ft_lstadd_back_env(envi, new);
	return (envi);
}

t_env	*lst_new_env_null(t_env *envi, char *str)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->str = ft_strdup(str);
	if (!new->str)
	{
		free(new);
		return (NULL);
	}
	new->next = NULL;
	new->prev = NULL;
	envi = ft_lstadd_back_env(envi, new);
	return (envi);
}
