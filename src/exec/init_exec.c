/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablevin <ablevin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:04:01 by ablevin           #+#    #+#             */
/*   Updated: 2023/05/20 13:04:02 by ablevin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_pipes(t_blocks *blocks)
{
	t_blocks	*tmp;

	tmp = blocks;
	while (tmp)
	{
		if (pipe(tmp->pipe) == -1)
			return (lst_clear_blocks(&blocks), 1);
		tmp = tmp->next;
	}
	return (0);
}

int	get_nb_cmds(t_blocks *blocks)
{
	int			nb_cmds;
	t_blocks	*tmp;

	nb_cmds = 0;
	tmp = blocks;
	while (tmp)
	{
		nb_cmds++;
		tmp = tmp->next;
	}
	return (nb_cmds);
}

int	*init_exec(t_blocks *blocks, t_env *env)
{
	int	*pid;
	int	nb_cmds;

	(void)env;
	nb_cmds = get_nb_cmds(blocks);
	if (init_pipes(blocks) == 1)
	{
		global_exit_status(errno);
		return (ft_putstr_fd("minishell: pipe error\n", 2), NULL);
	}
	heredoc(blocks, env);
	open_files(blocks);
	pid = malloc(sizeof(int) * nb_cmds);
	if (!pid)
	{
		lst_clear_blocks(&blocks);
		return (ft_putstr_fd("minishell: malloc error\n", 2), NULL);
	}
	return (pid);
}
