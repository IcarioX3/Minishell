#include "minishell.h"

void	check_pwd(t_pile *start)
{
	char cwd[1024];
	if (ft_strlen(start->str) == 3)
	{
		if (ft_strnstr(start->str, "pwd", 3) != NULL)
		{
			if (getcwd(cwd, sizeof(cwd)) != NULL) 
			{
				printf("Le répertoire de travail actuel est : %s\n", cwd);
			}
			else
			{
				perror("Erreur lors de l'appel à getcwd()");
				//return 1; a check egalement 
			}
		}
	}
}

void	check_env(t_pile *start, char **env)
{
	int	i;

	i = 0;
	if (ft_strlen(start->str) == 3)
	{
		if (ft_strnstr(start->str, "env", 3) != NULL)
		{
			while(env[i])
			{
				printf("%s\n", env[i]);
				i++;
			}
		}
	}	
}

void	check_echo(t_pile *start)
{
	if (ft_strlen(start->str) == 4 && ft_lstsize(start) > 1)
	{
		if (ft_strnstr(start->str, "echo", 4) != NULL)
		{
			if (strstr(start->next->str, "-n") != NULL)
				printf("%s", start->next->next->str);
			else
				printf("%s\n", start->next->str);
		}
	}	
}

void	check_builtin(t_pile *start, char **env)
{
	check_pwd(start); //possiblement a proteger si erreur de getcwd mais a voir a cause des leak...ne pas stopper le prog sans free et close.
	check_env(start, env); //affiche l'env avec la commande env.
	check_echo(start); // reproduis echo et echo -n a modifier car on peut mettre "echo -nnnnnnnn..." surement d'autre cas a gerer a tester avec bash pour voir le comportement.
}
