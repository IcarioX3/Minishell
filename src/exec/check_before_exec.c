/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_before_exec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablevin <ablevin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:03:48 by ablevin           #+#    #+#             */
/*   Updated: 2023/05/20 13:03:49 by ablevin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 1)
		return (1);
	else if (ft_strcmp(cmd, "cd") == 1)
		return (1);
	else if (ft_strcmp(cmd, "pwd") == 1)
		return (1);
	else if (ft_strcmp(cmd, "export") == 1)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 1)
		return (1);
	else if (ft_strcmp(cmd, "env") == 1)
		return (1);
	else if (ft_strcmp(cmd, "exit") == 1)
		return (1);
	return (0);
}

int	check_before_exec(t_blocks *blocks, t_env *env)
{
	t_redir	*tmp;

	tmp = blocks->redir;
	if (blocks->cmd[0] == NULL)
		return (1);
	while (tmp)
	{
		if (tmp->fd == -1)
			return (1);
		tmp = tmp->next;
	}
	if (is_builtin(blocks->cmd[0]))
		return (blocks->path = ft_strdup(blocks->cmd[0]), 0);
	if (access(blocks->cmd[0], F_OK | X_OK) == 0)
		blocks->path = ft_strdup(blocks->cmd[0]);
	else
	{
		blocks->path = get_bin_path(blocks->cmd[0], env);
		if (!blocks->path)
			return (1);
	}
	return (0);
}
