#include "minishell.h"

void	check_builtin(char **input, t_env **env)
{
	ft_pwd(input);
	ft_env(input, env);
	ft_cd(input);
	ft_echo(input);
	ft_unset(input, env);
	ft_export(input, env); //attention si j'export a=1 pui a=2 alore j'ecraserai le premier a
	//pour export si j'export une var deja existante je la remplace par la nouvelle erreur si je met un egale en premier
}

//reproduire getenv pour le dollar si la var est trouve alo je lui envoi tout ce qu'il y a derriere le egal