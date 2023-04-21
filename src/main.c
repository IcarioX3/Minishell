#include "minishell.h"

t_env	*lst_new_env(t_env *envi, char *str)
{
	t_env	*tmp;
	t_env	*new;

	new = (t_env *)malloc(sizeof(new));
	new->str = ft_strdup(str);
	new->next = NULL;
	if (envi == NULL)
		envi = new;
	else
	{
		tmp = new;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
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
		check_builtin(ui, env);
		tokens = lexer(input, tokens);
		//printf("After lexer:\n");
		//print_tokens(tokens);
		free(input);
		parser(&tokens);
		//printf("\nAfter parser:\n");
		//print_tokens(tokens);
		lst_clear_token(&tokens);
	}
	return (0);
}
