#include "minishell.h"

void	ft_exit(char **input, t_env **env, t_blocks **blocks, int *g_exit_status)
{
	
}

void	ft_check_exit(char **input, t_env **env, t_blocks **blocks, int *g_exit_status)
{
	if (ft_strlen(input[0]) == 4)
	{
		if (ft_strnstr(input[0], "exit", 4) != NULL)
		{
			ft_exit(input, env, blocks, g_exit_status);
		}
	}
}

