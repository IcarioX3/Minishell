/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablevin <ablevin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:04:19 by ablevin           #+#    #+#             */
/*   Updated: 2023/05/20 13:04:20 by ablevin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir(t_tokens *tokens)
{
	if (tokens->token == IN_REDIR || tokens->token == OUT_REDIR
		|| tokens->token == APPEND || tokens->token == HEREDOC)
		return (1);
	return (0);
}

t_tokens	*redir_parser(t_tokens *tokens)
{
	t_tokens	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (is_redir(tmp))
		{
			free(tmp->str);
			tmp->str = ft_strdup(tmp->next->str);
			del_token(tokens, tmp->next);
		}
		tmp = tmp->next;
	}
	return (tokens);
}
