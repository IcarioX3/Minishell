/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablevin <ablevin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:02:55 by ablevin           #+#    #+#             */
/*   Updated: 2023/05/20 13:02:56 by ablevin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_args(t_tokens *tokens)
{
	char	**args;
	int		i;

	args = malloc(sizeof(char *) * (count_args(tokens) + 1));
	if (!args)
		return (NULL);
	i = 0;
	while (tokens && tokens->token != PIPE)
	{
		if (tokens->token == WORD)
		{
			args[i] = ft_strdup(tokens->str);
			i++;
		}
		tokens = tokens->next;
	}
	args[i] = NULL;
	return (args);
}

void	init_var(t_blocks *new_block, t_tokens *tokens)
{
	new_block->path = NULL;
	new_block->env = NULL;
	new_block->nb_args = count_args(tokens);
	new_block->pipe[0] = -1;
	new_block->pipe[1] = -1;
	new_block->fd_in = -1;
	new_block->fd_out = -1;
	new_block->pid = NULL;
	new_block->next = NULL;
	new_block->prev = NULL;
	new_block->redir = get_redir(tokens);
}

t_blocks	*add_new_block(t_blocks *blocks, t_tokens *tokens)
{
	t_blocks	*new_block;
	t_blocks	*tmp;

	new_block = malloc(sizeof(t_blocks));
	if (!new_block)
		return (lst_clear_blocks(&blocks), NULL);
	new_block->cmd = get_args(tokens);
	new_block->nb_args = count_args(tokens);
	if (!new_block->cmd)
		return (lst_clear_blocks(&blocks), NULL);
	init_var(new_block, tokens);
	if (!blocks)
		return (new_block);
	tmp = blocks;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_block;
	new_block->prev = tmp;
	return (blocks);
}

t_blocks	*put_in_blocks(t_blocks *blocks, t_tokens *tokens)
{
	t_tokens	*tmp;

	tmp = tokens;
	while (tmp)
	{
		blocks = add_new_block(blocks, tmp);
		if (!blocks)
		{
			printf("minishell: malloc error\n");
			global_exit_status(1);
			return (NULL);
		}
		while (tmp && tmp->token != PIPE)
			tmp = tmp->next;
		if (tmp)
			tmp = tmp->next;
	}
	return (blocks);
}
