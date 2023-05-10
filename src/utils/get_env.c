#include "minishell.h"

char	*ft_getenv(char	*name, char **env)
{
	int	i;
	int	len;

	i = 0;
	len = strlen(name);
	while (env[i] != NULL)
	{
		if ((strncmp(name, env[i], len) == 0) && (env[i][len] == '='))
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}
