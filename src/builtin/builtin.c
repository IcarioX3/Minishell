#include "minishell.h"

int	check_builtin(char **input, t_env **env, t_blocks **blocks, int *g_exit_status, char **true_env)
{
	if (!input || !*input)
		return (0);
	ft_pwd(input);
	ft_env(input, env);
	if (ft_cd(env, input, g_exit_status, true_env) == 1)
		return (1);
	ft_echo(input);
	ft_unset(input, env);
	ft_check_exit(input, env, blocks, g_exit_status);
	if (ft_export(input, env) == 1)
		return (1);
	return (0);
}
