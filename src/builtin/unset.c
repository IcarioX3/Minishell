#include "minishell.h"

void del_env(t_env **env, t_env *node_to_remove)
{
	if (*env == NULL || node_to_remove == NULL)
		return ;
	if (*env == node_to_remove)
		*env = node_to_remove->next;
	if (node_to_remove->next != NULL)
        node_to_remove->next->prev = node_to_remove->prev;
	if (node_to_remove->prev != NULL)
	{
		if (node_to_remove->next == NULL)
		{
			node_to_remove->prev->next = NULL;
		}
		else
		{
			node_to_remove->prev->next = node_to_remove->next;
		}
	}
	free(node_to_remove->str);
    free(node_to_remove);
}

void	ft_check_unset(char *input, t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (*env)
	{
		if (ft_strnstr((*env)->str, input, ft_strlen(input)) != NULL 
			&& (*env)->str[ft_strlen(input)] == '=')
		{
			del_env(env, *env);
		}
		*env = (*env)->next;
	}
	printf("2\n");
	*env = tmp;
}

void	ft_unset(char **input, t_env **env)
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