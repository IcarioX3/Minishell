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

t_redir	*add_new_redir(t_redir *redir, t_tokens *tokens)
{
	t_redir *new_redir;
	t_redir *tmp;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return (lst_clear_redir(&redir), NULL);
	new_redir->file = ft_strdup(tokens->str);
	if (!new_redir->file)
		return (lst_clear_redir(&redir), NULL);
	new_redir->token = tokens->token;
	new_redir->next = NULL;
	if (!redir)
		return (new_redir);
	tmp = redir;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_redir;
	return (redir);
}

t_redir	*get_redir(t_tokens *tokens)
{
	t_redir *redir;

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
		redir = malloc(sizeof(t_redir));
		if (!redir)
			return (NULL);
		redir->file = NULL;
		redir->token = 0;
		redir->next = NULL;
	}
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
	new_block->nb_args = count_args(tokens);
	new_block->next = NULL;
	new_block->redir = get_redir(tokens);
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
			printf("minishell: malloc error\n");
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