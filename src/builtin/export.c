#include "minishell.h"

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

int	ft_is_export(char *input)
{
	int	i;

	i = 0;
	while (i <= get_pos_equal(input))
	{
		if ((input[i] > 0 && input[i] <= 47)
			|| (input[i] >= 58 && input[i] <= 60)
			|| (input[i] >= 62 && input[i] <= 64)
			|| (input[i] >= 91 && input[i] <= 94)
			|| (input[i] >= 123 && input[i] < 127)
			|| (input[i] == 96) || (input[0] == '=')
			|| (input[0] >= 48 && input[0] <= 57) || input[0] == '\\')
		{
			ft_putstr_fd("export: `", 2);
			ft_putstr_fd(input, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_export(char **input, t_env **env)
{
	int	i;

	i = 1;
	if (ft_strlen(input[0]) == 6)
	{
		if (ft_strnstr(input[0], "export", 6) != NULL)
		{
			if (input[1] == NULL)
				return (print_error("Usage : export var=value"), 0);
			while (input[i])
			{
				if ((ft_is_export(input[i]) != 0)
					|| (input[i][0] == '_' && input[i][1] == '='))
				{
					i++;
					continue ;
				}
				if (ft_check_export(input[i], *env) == 1)
					return (1);
				i++;
			}
		}
	}
	return (0);
}
