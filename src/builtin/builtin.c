#include "minishell.h"

int	check_builtin(char **input, t_env **env)
{
	ft_pwd(input);
	ft_env(input, env);
	ft_cd(input);
	ft_echo(input); //proleme quand je fait necho n a.
	ft_unset(input, env);
	if (ft_export(input, env) == 1)
		return (1);
	return (0);
}
//reproduire getenv pour le dollar si la var est trouve alo je lui envoi tout ce qu'il y a derriere le egal