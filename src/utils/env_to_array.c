/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablevin <ablevin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:04:33 by ablevin           #+#    #+#             */
/*   Updated: 2023/05/20 13:04:34 by ablevin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
