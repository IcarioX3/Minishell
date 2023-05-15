#include "minishell.h"

char	*ft_getenv(char	*name, t_env **env)
{
	int		len;
	t_env	*tmp;

	len = strlen(name);
	tmp = *env;
	while (*tmp)
	{
		if ((strncmp(name, tmp->str, len) == 0) && (tmp->str[len] == '='))
			return (tmp->str + len + 1);
		tmp = tmp->next;
	}
	return (NULL);
}
