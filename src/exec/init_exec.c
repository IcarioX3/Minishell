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

int	get_nb_cmds(t_blocks *blocks)
{
	int			nb_cmds;
	t_blocks	*tmp;

	nb_cmds = 0;
	tmp = blocks;
	while (tmp)
	{
		nb_cmds++;
		tmp = tmp->next;
	}
	return (nb_cmds);
}

int	*init_exec(t_blocks *blocks)
{
	int	*pid;
	int	nb_cmds;

	nb_cmds = get_nb_cmds(blocks);
	if (init_pipes(blocks) == 1)
	{
		global_exit_status(errno);
		return (ft_putstr_fd("minishell: pipe error\n", 2), NULL);
	}
	heredoc(blocks);
	open_files(blocks);
	pid = malloc(sizeof(int) * nb_cmds);
	if (!pid)
	{
		lst_clear_blocks(&blocks);
		return (ft_putstr_fd("minishell: malloc error\n", 2), NULL);
	}
	return (pid);
}
