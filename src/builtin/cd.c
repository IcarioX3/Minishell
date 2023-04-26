#include "minishell.h"

void	ft_cd(char **input) 
{
	if (ft_strlen(input[0]) == 2)
	{
		if (ft_strnstr(input[0], "cd", 2) != NULL)
		{
			if (input[1] == NULL) 
			{
				chdir("/");
			}
			else 
			{
				if (chdir(input[1]) != 0)
				{
					perror("cd");
				}
			}
		}
	}
}