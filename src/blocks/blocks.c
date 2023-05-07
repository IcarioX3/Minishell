#include "minishell.h"

int count_cmd(t_tokens *tokens)
{
	int count;

	count = 0;
	while (tokens)
	{
		if (tokens->token == PIPE)
			count++;
		tokens = tokens->next;
	}
	return (count + 1);
}

int count_args(t_tokens *tokens)
{
	int count;

	count = 0;
	while (tokens && tokens->token != PIPE)
	{
		if (tokens->token == WORD)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

int	count_redir(t_tokens *tokens)
{
	int count;

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

char	**get_args(t_tokens *tokens)
{
	char **args;
	int i;

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

t_redir	*get_redir(t_tokens *tokens)
{
	t_redir *redir;
	int 	i;

	redir = malloc(sizeof(t_redir) * (count_redir(tokens) + 1));
	if (!redir)
		return (NULL);
	i = 0;
	while (i < count_redir(tokens))g
	{
		redir[i].next = &redir[i + 1];
		i++;
	}
	redir[i].next = NULL;
	i = 0;
	while (tokens && tokens->token != PIPE)
	{
		if (tokens->token == IN_REDIR)
		{
			redir[i].token = IN_REDIR;
			redir[i].file = ft_strdup(tokens->str);
			if (!redir[i].file)
				return (lst_clear_redir(&redir), NULL);
			i++;
		}
		else if (tokens->token == OUT_REDIR)
		{
			redir[i].token = OUT_REDIR;
			redir[i].file = ft_strdup(tokens->str);
			if (!redir[i].file)
				return (lst_clear_redir(&redir), NULL);
			i++;
		}
		else if (tokens->token == APPEND)
		{
			redir[i].token = APPEND;
			redir[i].file = ft_strdup(tokens->next->str);
			if (!redir[i].file)
				return (lst_clear_redir(&redir), NULL);
			i++;
		}
		tokens = tokens->next;
	}
	redir->token = 0;
	redir[i].file = NULL;
	return (redir);
}

t_blocks	*add_new_block(t_blocks *blocks, t_tokens *tokens)
{
	t_blocks *new_block;
	t_blocks *tmp;

	new_block = malloc(sizeof(t_blocks));
	if (!new_block)
		return (lst_clear_blocks(&blocks), NULL);
	new_block->cmd = get_args(tokens);
	if (!new_block->cmd)
		return (lst_clear_blocks(&blocks), NULL);
	new_block->fd_in = -1;
	new_block->fd_out = -1;
	new_block->next = NULL;
	new_block->redir = get_redir(tokens);
	if (!new_block->redir)
		return (lst_clear_blocks(&blocks), NULL);
	if (!blocks)
		return (new_block);
	tmp = blocks;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_block;
	return (blocks);
}

t_blocks	*put_in_blocks(t_blocks *blocks, t_tokens *tokens, int *g_status)
{
	t_tokens *tmp;

	tmp = tokens;
	while (tmp)
	{
		blocks = add_new_block(blocks, tmp);
		if (!blocks)
		{
			*g_status = 1;
			return (NULL);
		}
		while (tmp && tmp->token != PIPE)
			tmp = tmp->next;
		if (tmp)
			tmp = tmp->next;
	}
	return (blocks);
}