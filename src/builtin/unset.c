#include "minishell.h"

void del_env(t_env *env, t_env *node_to_remove)
{
	t_env	*temp;

	temp = node_to_remove;
	if (env == NULL || node_to_remove == NULL)
		return ;
	if (node_to_remove->prev == NULL)
	{
		printf("1\n");
		env = node_to_remove->next;
		(env)->prev = NULL;
		temp = node_to_remove->next;
	}
	else if (node_to_remove->prev != NULL && node_to_remove->next != NULL)
	{
		printf("2\n");
		node_to_remove->prev->next = node_to_remove->next;
		node_to_remove->next->prev = node_to_remove->prev;
		node_to_remove = temp;
	}
	else
	{
		printf("3\n");
		node_to_remove->prev->next = NULL;
		node_to_remove = temp;
	}
    //free(node_to_remove); //a voir car me creer un segfault donc a gerer quand je ferais la partie leak
	free(node_to_remove->str);
}

void	ft_check_unset(char *input, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (env && env)
	{
		if (ft_strnstr((env)->str, input, ft_strlen(input)) != NULL 
			&& (env)->str[ft_strlen(input)] == '=')
		{
			del_env(env, env);
		}
		else
			env = (env)->next;
	}
	env = tmp;
}

void	ft_unset(char **input, t_env *env)
{
	int i;

	i = 1;
	if (input[1] == NULL)
		return ;
	if (ft_strlen(input[0]) == 5)
	{
		if (ft_strnstr(input[0], "unset", 5) != NULL)
		{
			while (input[i])
			{
				ft_check_unset(input[i], env);
				i++;
			}
		}
	}
}
