#include "minishell.h"

void	ft_env(char **input, t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	if (env == NULL)
		return ;
	if (ft_strlen(input[0]) == 3)
	{
		if (ft_strnstr(input[0], "env", 3) != NULL)
		{
			while (*env)
			{
				printf("%s\n", (*env)->str);
				*env = (*env)->next;
			}
		}
	}
	*env = tmp;
}
