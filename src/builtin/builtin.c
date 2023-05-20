/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablevin <ablevin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:03:02 by ablevin           #+#    #+#             */
/*   Updated: 2023/05/20 13:03:03 by ablevin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtin(char **input, t_env **env, t_blocks **blocks, t_blocks *b)
{
	if (!input || !*input)
		return (0);
	ft_pwd(input);
	ft_env(input, env);
	if (ft_cd(env, input) == 1)
		return (1);
	ft_echo(input, b);
	ft_unset(input, env);
	ft_check_exit(input, env, blocks);
	if (ft_export(input, env) == 1)
		return (1);
	return (0);
}
