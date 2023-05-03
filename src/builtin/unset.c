#include "minishell.h"

void del_env(t_env **remove)
{
	t_env	*tmp;

	tmp = *remove;
	if ((*remove)->prev == NULL && (*remove)->next != NULL)
	{
		*remove = (*remove)->next;
		(*remove)->prev = NULL; 
	}
	else if ((*remove)->prev != NULL && (*remove)->next != NULL)
	{
		(*remove)->next->prev = (*remove)->prev;
		(*remove)->prev->next = (*remove)->next;
	}
	else if ((*remove)->next == NULL && (*remove)->prev != NULL)
	{
		(*remove)->prev->next = NULL;
	}
	free(tmp->str);
	free(tmp);
}

void	ft_check_unset(char *input, t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	int		poseg;
	int i = 0;

	poseg = 0;
	while (input[poseg] != 0)
		poseg++;
	while (*env && i == 0)
	{
		if (ft_strncmp((*env)->str, input, poseg) == 0 && i == 0)
		{
			del_env(env);
			i = 1;
			break ;
		}
		else
			*env = (*env)->next;
	}
	if (env)
		*env = tmp;
}

void	ft_unset(char **input, t_env **env)
{
	int i;

	i = 1;
	if (input[1] == NULL || (ft_strlen(input[1]) == 1 && input[1][0] == '_'))
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
