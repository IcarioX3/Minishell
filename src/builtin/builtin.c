#include "minishell.h"

int	check_builtin(char **input, t_env **env)
{
	ft_pwd(input);
	ft_env(input, env);
	ft_cd(input);
	ft_echo(input);
	ft_unset(input, env);
	if (ft_export(input, env) == 1)
		return (1);
	return (0);
}
