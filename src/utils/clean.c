#include "minishell.h"

void	clean_all(t_blocks *blocks, t_env *envi)
{
	lst_clear_blocks(&blocks);
	lst_clear_env(envi);
}