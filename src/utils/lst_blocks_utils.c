/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_blocks_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablevin <ablevin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:04:38 by ablevin           #+#    #+#             */
/*   Updated: 2023/05/20 13:04:39 by ablevin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmd(t_tokens *tokens)
{
	int	count;

	count = 0;
	while (tokens)
	{
		if (tokens->token == PIPE)
			count++;
		tokens = tokens->next;
	}
	return (count + 1);
}

int	count_args(t_tokens *tokens)
{
	int	count;

	count = 0;
	while (tokens && tokens->token != PIPE)
	{
		if (tokens->token == WORD)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

void	lst_clear_redir(t_redir **redir)
{
	t_redir	*tmp;

	if (!redir)
		return ;
	while (*redir)
	{
		tmp = *redir;
		*redir = (*redir)->next;
		if (tmp)
			free(tmp->file);
		if (tmp->fd != -1 && tmp->fd != -2)
			close(tmp->fd);
		free(tmp);
	}
}

void	close_pipes(t_blocks *blocks)
{
	t_blocks	*tmp;
	t_redir		*tmp_redir;

	tmp = blocks;
	while (tmp)
	{
		if (tmp->pipe[0] != -1)
			close(tmp->pipe[0]);
		if (tmp->pipe[1] != -1)
			close(tmp->pipe[1]);
		if (tmp->fd_in != -1 && tmp->fd_in != -2)
			close(tmp->fd_in);
		if (tmp->fd_out != -1 && tmp->fd_out != -2)
			close(tmp->fd_out);
		tmp_redir = tmp->redir;
		while (tmp_redir)
		{
			if (tmp_redir->pipe_heredoc[0] != -1)
				close(tmp_redir->pipe_heredoc[0]);
			if (tmp_redir->pipe_heredoc[1] != -1)
				close(tmp_redir->pipe_heredoc[1]);
			tmp_redir = tmp_redir->next;
		}
		tmp = tmp->next;
	}
}

void	lst_clear_blocks(t_blocks **blocks)
{
	t_blocks	*tmp;

	if (blocks == NULL)
		return ;
	while (*blocks)
	{
		tmp = *blocks;
		*blocks = (*blocks)->next;
		if (tmp->cmd)
		{
			while (tmp->nb_args > 0)
			{
				if (tmp->cmd[tmp->nb_args - 1] != NULL)
					free(tmp->cmd[tmp->nb_args - 1]);
				tmp->nb_args--;
			}
			free(tmp->cmd);
		}
		close_pipes(tmp);
		lst_clear_redir(&tmp->redir);
		free(tmp->pid);
		free_double_array(tmp->env);
		free(tmp->path);
		free(tmp);
	}
}
