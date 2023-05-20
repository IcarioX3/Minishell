/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablevin <ablevin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:04:36 by ablevin           #+#    #+#             */
/*   Updated: 2023/05/20 13:04:37 by ablevin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char	*name, t_env **env)
{
	int		len;
	t_env	*tmp;

	len = strlen(name);
	tmp = *env;
	while (tmp)
	{
		if ((strncmp(name, tmp->str, len) == 0) && (tmp->str[len] == '='))
			return (tmp->str + len + 1);
		tmp = tmp->next;
	}
	return (NULL);
}
