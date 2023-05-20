/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablevin <ablevin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:10:59 by ablevin           #+#    #+#             */
/*   Updated: 2023/05/20 13:11:08 by ablevin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_heredoc(t_tokens *tokens)
{
	t_tokens	*tmp;

	tmp = tokens;
	while (tmp->previous && (tmp->previous->token == HEREDOC
			|| tmp->previous->token == SEP))
	{
		if (tmp->previous->token == HEREDOC)
			return (1);
		tmp = tmp->previous;
	}
	return (0);
}
