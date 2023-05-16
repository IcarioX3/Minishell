#include "minishell.h"

void	free_double_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	clean_all(t_blocks *blocks, t_env *envi)
{
	lst_clear_blocks(&blocks);
	lst_clear_env(envi);
}