#include "minishell.h"

int	init_pipes(t_blocks *blocks)
{
	t_blocks	*tmp;

	tmp = blocks;
	while (tmp)
	{
		if (pipe(tmp->pipe) == -1)
			return (lst_clear_blocks(&blocks), 1);
		tmp = tmp->next;
	}
	return (0);
}

int	exec(t_blocks *blocks, t_env *env)
{
	(void)env;
	if (init_pipes(blocks) == 1)
		return (ft_putstr_fd("minishell: pipe error\n", 2), 1);
	open_files(blocks);
	return (0);
}
