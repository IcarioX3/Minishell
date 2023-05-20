/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redir_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablevin <ablevin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:09:19 by ablevin           #+#    #+#             */
/*   Updated: 2023/05/20 13:11:16 by ablevin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redir_out(t_blocks *blocks)
{
	t_redir		*tmp_redir;

	tmp_redir = blocks->redir;
	while (tmp_redir)
	{
		if (tmp_redir->token == APPEND || tmp_redir->token == OUT_REDIR)
			return (1);
		tmp_redir = tmp_redir->next;
	}
	return (0);
}

int	check_redir_in(t_blocks *blocks)
{
	t_redir		*tmp_redir;

	tmp_redir = blocks->redir;
	while (tmp_redir)
	{
		if (tmp_redir->token == IN_REDIR)
			return (1);
		tmp_redir = tmp_redir->next;
	}
	return (0);
}
