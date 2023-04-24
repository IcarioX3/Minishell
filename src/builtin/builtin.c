#include "minishell.h"

int	ft_pwd(char **input)
{
	char	cwd[1024];

	if (ft_strlen(input[0]) == 3)
	{
		if (ft_strnstr(input[0], "pwd", 3) != NULL)
		{
			if (input[1] && input[1][0] == '-')
			{
				printf("pwd: -%c: invalid option\n", input[1][1]);
				return (1);
			}
			if (getcwd(cwd, sizeof(cwd)) != NULL) 
				printf("%s\n", cwd);
			else
			{
				perror("Erreur lors de l'appel à getcwd()");
				return (1);
			}
		}
	}
	return (0);
}

void	ft_env(char **input, t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	if (ft_strlen(input[0]) == 3)
	{
		if (ft_strnstr(input[0], "env", 3) != NULL)
		{
			while (*env)
			{
				printf("%s\n", (*env)->str);
				*env = (*env)->next;
			}
		}
	}
	*env = tmp;
}

void ft_cd(char **input) 
{
	if (ft_strlen(input[0]) == 2)
	{
		if (ft_strnstr(input[0], "cd", 2) != NULL)
		{
			if (input[1] == NULL) 
			{
				chdir("/");
			} 
			else 
			{
				if (chdir(input[1]) != 0) 
				{
					perror("cd");
				}
			}
		}
	}
}

int	ft_nflag(char *input)
{
	int i;
	int len;

	i = 1;
	len = 0;
	if (!input)
		return (0);
	while (input[len])
		len++;
	while (input[i] == 'n')
		i++;
	if (len == 1)
		printf("%s\n", input);
	if (i == len)
		return (1);
	else
		return (0);
}

void ft_echo(char **input) 
{
	int i = 1;
	int nflag = 0;

	if (ft_strlen(input[0]) == 4)
	{
		if (ft_strnstr(input[0], "echo", 4) != NULL)
		{
			if (input[1] != NULL && ft_nflag(input[1]) == 1)
			{
				nflag = 1;
				i++;
			}
			while (input[i])
			{
				printf("%s", input[i]);
				i++;
				if (input[i] != NULL) 
					printf(" ");
			}
			if (nflag == 0)
			{
				printf("\n");
			}
		}
	}
}

void del_env(t_env **env, t_env *node_to_remove)
{
    if (*env == NULL || node_to_remove == NULL)
        return;
    // Si le maillon à supprimer est la tête de la liste
    if (*env == node_to_remove)
        *env = node_to_remove->next;

    // Si le maillon à supprimer n'est pas la tête de la liste
    if (node_to_remove->next != NULL)
        node_to_remove->next->prev = node_to_remove->prev;

    if (node_to_remove->prev != NULL)
        node_to_remove->prev->next = node_to_remove->next;

    free(node_to_remove->str);
    free(node_to_remove);
}

void	ft_check_unset(char *input, t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (*env)
	{
		if (ft_strnstr((*env)->str, input, ft_strlen(input)) != NULL && (*env)->str[ft_strlen(input)] == '=')
		{
			del_env(env, *env);
		}
		*env = (*env)->next;
	}
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
			printf("str = %s\n", (*env)->str);
			*env = lst_new_env(*env, input);
			break ;
		}
		*env = (*env)->next;
	}
	*env = tmp;
}

void	ft_export(char **input, t_env **env)
{
		int i;

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

void	check_builtin(char **input, t_env **env)
{
	ft_pwd(input);
	ft_env(input, env);
	ft_cd(input);
	ft_echo(input);
	ft_unset(input, env); //probleme quand je supprime la derniere variable de ma liste
	ft_export(input, env); //attention si j'export a=1 pui a=2 alore j'ecraserai le premier a
	//pour export si j'export une var deja existante je la remplace par la nouvelle erreur si je met un egale en premier
}