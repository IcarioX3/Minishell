#include "minishell.h"

void	lst_clear_token(t_tokens **tokens)
{
	t_tokens	*tmp;

	if (tokens == NULL)
		return ;
	while (*tokens)
	{
		tmp = *tokens;
		*tokens = (*tokens)->next;
		free(tmp->str);
		free(tmp);
	}
	tokens = NULL;
}

t_tokens	*lst_new_token(t_tokens *tokens, char *s, int token)
{
	t_tokens	*new;
	t_tokens	*tmp;

	new = (t_tokens *)malloc(sizeof(t_tokens));
	if (new == NULL)
		return (NULL);
	new->str = s;
	if (new->str == NULL)
		return (NULL);
	new->token = token;
	new->next = NULL;
	new->previous = NULL;
	if (tokens == NULL)
		return (new);
	tmp = tokens;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->previous = tmp;
	return (tokens);
}
