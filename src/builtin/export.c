#include "minishell.h"

// int	ft_check_export(char *input, t_env *env)
// {
// 	int		poseg;

// 	poseg = 0;
// 	if (ft_strlen(input) < 2)
// 		return (0);
// 	while (input[poseg] != '=')
// 		poseg++;
// 	while (env)
// 	{
// 		if (ft_strncmp((env)->str, input, poseg + 1) == 0)
// 		{
// 			free(env->str);
// 			env->str = ft_strdup(input);
// 			if (!env->str)
// 				return (1);
// 			break ;
// 		}
// 		else if ((env)->next == NULL)
// 		{
// 			if (lst_new_env(env, input) == NULL)
// 				return (1);
// 			break;
// 		}
// 		env = (env)->next;
// 	}
// 	if (!env)
// 	{
// 		if (lst_new_env(env, input) == NULL)
// 			return (1);
// 	}
// 	return (0);
// }


int	get_pos_equal(char *input)
{
	int	pos;

	pos = 0;
	while (input[pos] != '=')
	{
		if (input[pos] == '\0')
			return (0);
		pos++;
	}
	return (pos);
}

int	update_env(char *input, t_env *env)
{
	free(env->str);
	env->str = ft_strdup(input);
	if (!env->str)
		return (1);
	return (0);
}

int	create_env(char *input, t_env *env)
{
	if (lst_new_env(env, input) == NULL)
		return (1);
	return (0);
}

int	ft_check_export(char *input, t_env *env)
{
	int	pos_eg;

	pos_eg = get_pos_equal(input);
	if (ft_strlen(input) < 2 || pos_eg == 0)
		return (0);
	while (env)
	{
		if (ft_strncmp(env->str, input, pos_eg + 1) == 0)
			return (update_env(input, env));
		else if (env->next == NULL)
			return (create_env(input, env));
		env = env->next;
	}
	if (!env)
		return (create_env(input, env));
	return (0);
}

int	ft_export(char **input, t_env **env)
{
	int	i;

	i = 1;
	if (input[1] == NULL)
		return (0);
	if (ft_strlen(input[0]) == 6)
	{
		if (ft_strnstr(input[0], "export", 6) != NULL)
		{
			while (input[i])
			{
				if (input[i][0] == '=')
					return (0);
				if (ft_check_export(input[i], *env) == 1)
					return (1);
				i++;
			}
		}
	}
	return (0);
}
