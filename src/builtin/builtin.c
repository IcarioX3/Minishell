#include "minishell.h"

int	ft_pwd(char **input)
{
	char	cwd[1024];

	if (ft_strlen(input[0]) == 3)
	{
		if (ft_strnstr(input[0], "pwd", 3) != NULL)
		{
			if (input[1] && input[1][0] == '-')
			{
				printf("pwd: -%c: invalid option\n", input[1][1]);
				return (1);
			}
			if (getcwd(cwd, sizeof(cwd)) != NULL) 
				printf("%s\n", cwd);
			else
			{
				perror("Erreur lors de l'appel à getcwd()");
				return (1);
			}
		}
	}
	return (0);
}

void	check_builtin(char **input, char **env)
{
	(void)env;
	ft_pwd(input);
	//ft_env(input, env);
}