/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablevin <ablevin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:03:17 by ablevin           #+#    #+#             */
/*   Updated: 2023/05/20 13:03:18 by ablevin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(char **input, t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	if (env == NULL)
		return ;
	if (ft_strlen(input[0]) == 3)
	{
		if (ft_strnstr(input[0], "env", 3) != NULL)
		{
			while (*env)
			{
				printf("%s\n", (*env)->str);
				*env = (*env)->next;
			}
		}
	}
	*env = tmp;
}
