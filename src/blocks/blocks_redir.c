/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablevin <ablevin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:02:52 by ablevin           #+#    #+#             */
/*   Updated: 2023/05/20 13:02:53 by ablevin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_redir(t_tokens *tokens)
{
	int	count;

	count = 0;
	while (tokens && tokens->token != PIPE)
	{
		if (tokens->token == IN_REDIR || tokens->token == OUT_REDIR
			|| tokens->token == APPEND)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

t_redir	*add_new_redir(t_redir *redir, t_tokens *tokens)
{
	t_redir	*new_redir;
	t_redir	*tmp;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return (lst_clear_redir(&redir), NULL);
	new_redir->file = ft_strdup(tokens->str);
	if (!new_redir->file)
		return (lst_clear_redir(&redir), NULL);
	new_redir->token = tokens->token;
	new_redir->next = NULL;
	new_redir->pipe_heredoc[0] = -1;
	new_redir->pipe_heredoc[1] = -1;
	new_redir->fd = -2;
	if (!redir)
		return (new_redir);
	tmp = redir;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_redir;
	return (redir);
}

t_redir	*redir_null(t_redir *redir)
{
	if (redir == NULL)
	{
		redir = malloc(sizeof(t_redir));
		if (!redir)
			return (NULL);
		redir->file = NULL;
		redir->token = 0;
		redir->next = NULL;
		redir->pipe_heredoc[0] = -1;
		redir->pipe_heredoc[1] = -1;
		redir->fd = -2;
	}
	return (redir);
}

t_redir	*get_redir(t_tokens *tokens)
{
	t_redir	*redir;

	redir = NULL;
	while (tokens && tokens->token != PIPE)
	{
		if (tokens->token == IN_REDIR || tokens->token == OUT_REDIR
			|| tokens->token == APPEND || tokens->token == HEREDOC)
		{
			redir = add_new_redir(redir, tokens);
			if (!redir)
				return (lst_clear_redir(&redir), NULL);
		}
		tokens = tokens->next;
	}
	if (redir == NULL)
	{
		redir = redir_null(redir);
		if (!redir)
			return (lst_clear_redir(&redir), NULL);
	}
	return (redir);
}
