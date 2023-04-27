#include "minishell.h"

void	ft_check_export(char *input, t_env *env)
{
	t_env	*tmp;
	int		poseg;

	tmp = env;
	poseg = 0;
	if (ft_strlen(input) < 2)
		return ;
	while (input[poseg] != '=')
		poseg++;
	while (env)
	{
		if (ft_strncmp((env)->str, input, poseg + 1) == 0)
		{
			del_env(env, env);
			env = tmp;
			lst_new_env(env, input);
			break ;
		}
		else if ((env)->next == NULL)
			lst_new_env(env, input);
		env = (env)->next;
	}
	env = tmp;
}

void	ft_export(char **input, t_env *env)
{
	int	i;

	i = 1;
	if (input[1] == NULL)
		return ;
	if (ft_strlen(input[0]) == 6)
	{
		if (ft_strnstr(input[0], "export", 6) != NULL)
		{
			while (input[i])
			{
				if (input[i][0] == '=')
					return ;
				ft_check_export(input[i], env);
				i++;
			}
		}
	}
}
