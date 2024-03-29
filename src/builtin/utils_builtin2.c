/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablevin <ablevin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:03:36 by ablevin           #+#    #+#             */
/*   Updated: 2023/05/20 13:03:37 by ablevin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*lst_env_error(t_env *envi)
{
	lst_clear_env(envi);
	return (NULL);
}

t_env	*lst_env_create_defaults(t_env *envi)
{
	char	*tmp;
	char	*tmp2;
	char	cwd[1024];

	tmp = NULL;
	tmp2 = ft_strdup("PWD=");
	envi = lst_new_env_null(envi, getcwd(cwd, sizeof(cwd)));
	if (!envi || !tmp2)
		return (lst_env_error(envi));
	tmp = ft_strjoin(tmp2, envi->str);
	if (!tmp)
		return (lst_env_error(envi));
	free(envi->str);
	envi->str = ft_strdup(tmp);
	if (!envi->str)
		return (lst_env_error(envi));
	envi = lst_new_env_null(envi, "SHLVL=1");
	if (!envi)
		return (lst_env_error(envi));
	envi = lst_new_env_null(envi, "_=/usr/bin/env");
	if (!envi)
		return (lst_env_error(envi));
	free(tmp);
	return (envi);
}

void	add_under_score(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp->next != NULL)
		tmp = tmp->next;
	if (tmp->str[0] != '_')
		tmp = lst_new_env_null(*env, "_=/usr/bin/env");
}

t_env	*lst_env(char **env)
{
	t_env	*envi;
	int		i;

	i = 0;
	envi = NULL;
	while (*env && env[i])
	{
		envi = lst_new_env(envi, env[i]);
		if (!envi)
			return (lst_env_error(envi));
		i++;
	}
	if (*env == NULL)
		envi = lst_env_create_defaults(envi);
	add_under_score(&envi);
	return (envi);
}
