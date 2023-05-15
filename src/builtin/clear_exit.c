#include "minishell.h"

void	ft_clear_all(t_env **env, t_blocks **blocks)
{
	lst_clear_blocks(blocks);
	lst_clear_env(*env);
}
