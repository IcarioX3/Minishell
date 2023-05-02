#include "minishell.h"

int	count_pipe(t_tokens *tokens)
{
	int			i;
	t_tokens	*tmp;

	i = 0;
	tmp = tokens;
	while (tmp)
	{
		if (tmp->token == PIPE)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

t_blocks	*add_new_block(t_blocks *blocks)
{
	t_blocks	*new;
	t_blocks	*tmp;

	new = (t_blocks *)malloc(sizeof(t_blocks));
	if (new == NULL)
	{
		lst_clear_block(&blocks);
		error_exit("malloc error", 1);
		return (NULL);
	}
	new->cmd = NULL;
	new->heredoc = NULL;
	new->in = NULL;
	new->out = NULL;
	new->append = NULL;
	new->next = NULL;
	if (blocks == NULL)
		return (new);
	tmp = blocks;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (blocks);
}

t_blocks	*set_count(t_blocks *blocks, t_tokens *tokens)
{
	while(tokens && tokens->token != PIPE)
	{
		if (tokens->token == IN_REDIR)
			blocks->in_count++;
		else if (tokens->token == OUT_REDIR)
			blocks->out_count++;
		else if (tokens->token == APPEND)
			blocks->append_count++;
		else if (tokens->token == HEREDOC)
			blocks->heredoc_count++;
		else if (tokens->token == WORD)
			blocks->cmd_count++;
		tokens = tokens->next;
	}
	return (blocks);
}
t_blocks	*put_in_blocks(t_blocks *blocks, t_tokens *tokens)
{
	int nb_blocks;

	nb_blocks = count_pipe(tokens) + 1;
	while (nb_blocks--)
	{
		blocks = add_new_block(blocks);
		blocks = set_count(blocks, tokens);
	}
	return (blocks);
}
