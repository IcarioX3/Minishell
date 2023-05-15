#include "minishell.h"

int	create_env(char *input, t_env *env)
{
	if (lst_new_env(env, input) == NULL)
		return (1);
	return (0);
}
