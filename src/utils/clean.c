/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablevin <ablevin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:04:30 by ablevin           #+#    #+#             */
/*   Updated: 2023/05/20 13:04:31 by ablevin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_double_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	clean_all(t_blocks *blocks, t_env *envi)
{
	lst_clear_blocks(&blocks);
	lst_clear_env(envi);
}

void	clean_all_exit(t_blocks *blocks, t_env *envi, int exit_code)
{
	clean_all(blocks, envi);
	exit(exit_code);
}
