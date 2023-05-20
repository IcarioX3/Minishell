/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablevin <ablevin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:03:09 by ablevin           #+#    #+#             */
/*   Updated: 2023/05/20 13:03:10 by ablevin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_home(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strnstr(tmp->str, "HOME", 4) != NULL)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	check_arg_cd(char **input)
{
	if (input[1] == NULL)
		return (0);
	if (input[2] != NULL)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		global_exit_status(1);
		return (1);
	}
	return (0);
}
