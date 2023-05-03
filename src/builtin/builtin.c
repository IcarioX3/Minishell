#include "minishell.h"

void	check_builtin(char **input, t_env **env)
{
	ft_pwd(input);
	ft_env(input, env);
	ft_cd(input);
	ft_echo(input); //proleme quand je fait necho n a. 
	ft_unset(input, env);
	ft_export(input, env);
}
//reproduire getenv pour le dollar si la var est trouve alo je lui envoi tout ce qu'il y a derriere le egal