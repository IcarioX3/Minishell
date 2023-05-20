/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablevin <ablevin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:03:21 by ablevin           #+#    #+#             */
/*   Updated: 2023/05/20 13:03:22 by ablevin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_all_num(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] < 48 || cmd[i] > 57)
			return (1);
		i++;
	}
	return (0);
}

void	ft_exit_one(t_env **env, t_blocks **blocks)
{
	ft_clear_all(env, blocks);
	printf("exit\n");
	exit (return_global_exit_status());
}

void	ft_exit_two(t_env **env, t_blocks **blocks)
{
	t_blocks	*tmp;
	int			cmd;

	tmp = *blocks;
	cmd = 0;
	if (is_all_num(tmp->cmd[1]) == 0)
	{
		cmd = ft_atoi(tmp->cmd[1]);
		if (cmd >= 0 && cmd <= 255)
		{
			ft_clear_all(env, blocks);
			global_exit_status(cmd);
			printf("exit\n");
			exit (return_global_exit_status());
		}
	}
	else
	{
		ft_clear_all(env, blocks);
		global_exit_status(2);
		ft_putstr_fd("exit: numeric argument required\n", 2);
		exit (return_global_exit_status());
	}
}

void	ft_exit_tree(t_env **env, t_blocks **blocks)
{
	t_blocks	*tmp;
	int			cmd;

	tmp = *blocks;
	cmd = 0;
	if (is_all_num(tmp->cmd[1]) == 1)
	{
		if (cmd >= 0 && cmd <= 255)
		{
			ft_clear_all(env, blocks);
			global_exit_status(2);
			printf("exit\n");
			ft_putstr_fd("exit: numeric argument required\n", 2);
			exit (return_global_exit_status());
		}
	}
	else
	{
		global_exit_status(1);
		printf("exit\n");
		ft_putstr_fd("exit: too many arguments\n", 2);
	}	
}

void	ft_check_exit(char **input, t_env **env, t_blocks **blocks)
{
	int	len;

	len = 0;
	while ((*blocks)->cmd[len])
		len++;
	if (ft_strlen(input[0]) == 4)
	{
		if (ft_strnstr(input[0], "exit", 4) != NULL)
		{
			if (len == 1)
				ft_exit_one(env, blocks);
			else if (len == 2)
				ft_exit_two(env, blocks);
			else if (len > 2)
				ft_exit_tree(env, blocks);
		}
	}
}
