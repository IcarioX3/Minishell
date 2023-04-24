#include "minishell.h"

void	lst_clear_env(t_env **envi)
{
	t_env	*tmp;

	if (envi == NULL)
		return ;
	while (*envi)
	{
		tmp = *envi;
		*envi = (*envi)->next;
		if (tmp->str)
			free(tmp->str);
		free(tmp);
	}
	envi = NULL;
}

t_env	*ft_lstlast_env(t_env *env)
{
	while (env)
	{
		if (env->next == NULL)
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	ft_lstadd_back_env(t_env **env, t_env *new)
{
	t_env	*tmp;

	if (*env == NULL)
	{
		*env = new;
	}
	else
	{
		tmp = ft_lstlast_env(*env);
		tmp->next = new;
		new->prev = tmp;
	}
}


t_env	*lst_new_env(t_env *envi, char *str)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	new->str = ft_strdup(str);
	new->next = NULL;
	new->prev = NULL;
	if (envi == NULL)
		envi = new;
	else
		ft_lstadd_back_env(&envi, new);
	return (envi);
}

t_env	*lst_env(t_env *envi, char **env)
{
	int i;

	i = 0;
	while (env[i] != NULL)
	{
		envi = lst_new_env(envi, env[i]);
		i++;
	}
	return (envi);
}

int	main(int argc, char **argv, char **env)
{
	char		*input;
	t_tokens	*tokens;
	t_env		*envi = NULL;
	char		**ui;

	(void)argv;
	tokens = NULL;
	if (argc != 1)
		return (1);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	envi = lst_env(envi, env);
	while (1)
	{
		input = readline("\033[36mminishell$\033[0m ");
		add_history(input);
		if (!input)
		{
			free(input);
			break ;
		}
		ui = ft_split(input, ' ');
		check_builtin(ui, &envi);
		tokens = lexer(input, tokens);
		//printf("After lexer:\n");
		//print_tokens(tokens);
		free(input);
		parser(&tokens);
		//printf("\nAfter parser:\n");
		//print_tokens(tokens);
		lst_clear_token(&tokens);
	}
	lst_clear_env(&envi); //probleme de leak a coriger a l'ecole
	return (0);
}
