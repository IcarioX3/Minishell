#include "minishell.h"

void	ft_check_export(char *input, t_env **env)
{
	t_env	*tmp;
	int flag;

	tmp = *env;
	flag = 0;
	int eg = 0;

	while (input[eg] != '=')
		eg++;
	eg++;
	while (*env)
	{
		if (ft_strnstr((*env)->str, input, eg + 1) != NULL)
			flag = 1;
		*env = (*env)->next;
	}

	*env = tmp;
	while (*env)
	{
		if (flag == 0 && ft_strchr(input, '=') != NULL)
		{
			printf("OK\n");
			*env = lst_new_env(*env, input);
			break ;
		}
		*env = (*env)->next;
	}
	*env = tmp;
}

void	ft_export(char **input, t_env **env)
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
				ft_check_export(input[i], env);
				i++;
			}
		}
	}
}