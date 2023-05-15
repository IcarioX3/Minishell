#include "minishell.h"

int	ft_home(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strnstr(tmp->str, "HOME", 4) != NULL)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
