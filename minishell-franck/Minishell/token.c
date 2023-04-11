#include "minishell.h"

int	get_token(t_pile *start)
{
	t_pile	*tmp;

	tmp = start;
	while (start)
	{
		get_token_sign(start);
		start = start->next;
	}
	start = tmp;
	return (0);
}

void	get_token_sign(t_pile *start)
{
	start->token = WORD;
	if (ft_strstr(start->str, "|") != NULL)
		start->token = PIPE;
	else if (ft_strstr(start->str, ">>") != NULL)
		start->token = RGT_HRDC;
	else if (ft_strstr(start->str, "<<") != NULL)
		start->token = LFT_HRDC;
	else if (ft_strstr(start->str, "<") != NULL)
		start->token = LFT_RDIR;
	else if (ft_strstr(start->str, ">") != NULL)
		start->token = RGT_RDIR;
}