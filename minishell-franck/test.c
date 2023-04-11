/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franck <franck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 02:51:46 by nbled             #+#    #+#             */
/*   Updated: 2023/04/11 13:34:01 by franck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	if (*to_find == '\0')
		return (NULL);
	while (str[i])
	{

		j = 0;
		while (str[i + j] == to_find[j])
		{
			j++;
			if (to_find[j] == '\0')
				return (&str[i]);
		}
		i++;
	}
	return (NULL);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (needle[i] == 0)
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		j = 0;
		while (needle[j] == haystack[i + j] && (i + j) < len)
		{
			j++;
			if (needle[j] == 0)
				return ((char *)&haystack[i]);
		}
		i++;
	}
	return (NULL);
}

void	get_token_sign(t_pile *start)
{
	start->token = WORD;
	if (ft_strstr(start->str, "|") != NULL)
		start->token = PIPE;
	else if (ft_strstr(start->str, ">>") != NULL)
		start->token = RGT_HRDC;
	else if (ft_strstr(start->str, "<<") != NULL)
		start->token = LFT_HRDC;
	else if (ft_strstr(start->str, "<") != NULL)
		start->token = LFT_RDIR;
	else if (ft_strstr(start->str, ">") != NULL)
		start->token = RGT_RDIR;
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
		i++;
	return (i);
}

int	get_token(t_pile *start)
{
	t_pile	*tmp;

	tmp = start;
	while (start)
	{
		get_token_sign(start);
		start = start->next;
	}
	start = tmp;
	return (0);
}

void	check_pwd(t_pile *start)
{
	char cwd[1024];
	if (ft_strlen(start->str) == 3)
	{
		if (ft_strnstr(start->str, "pwd", 3) != NULL)
		{
			if (getcwd(cwd, sizeof(cwd)) != NULL) 
			{
				printf("Le répertoire de travail actuel est : %s\n", cwd);
			}
			else
			{
				perror("Erreur lors de l'appel à getcwd()");
				//return 1; a check egalement 
			}
		}
	}
}

void	check_env(t_pile *start, char **env)
{
	int	i;

	i = 0;
	if (ft_strlen(start->str) == 3)
	{
		if (ft_strnstr(start->str, "env", 3) != NULL)
		{
			while(env[i])
			{
				printf("%s\n", env[i]);
				i++;
			}
		}
	}	
}

void	check_echo(t_pile *start)
{
	if (ft_strlen(start->str) == 4 && ft_lstsize(start) > 1)
	{
		if (ft_strnstr(start->str, "echo", 4) != NULL)
		{
			if (strstr(start->next->str, "-n") != NULL)
				printf("%s", start->next->next->str);
			else
				printf("%s\n", start->next->str);
		}
	}	
}

void	check_builtin(t_pile *start, char **env)
{
	check_pwd(start); //possiblement a proteger si erreur de getcwd mais a voir a cause des leak...ne pas stopper le prog sans free et close.
	check_env(start, env); //affiche l'env avec la commande env.
	check_echo(start); // reproduis echo et echo -n a modifier car on peut mettre "echo -nnnnnnnn..." surement d'autre cas a gerer a tester avec bash pour voir le comportement.
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_pile	*start;
	t_pile	*tmp;
	char	**splited;
	char	*str;
	size_t	i;

	i = 0;
	while (1)
	{
		i = 1;
		str = readline(BLUE"minishell : "END);
		if (str[0] && quote_check(str) == 0) //check si il y a le bon nombre de single/double quote
		{
			splited = ft_split(str);
			start = ft_lstnew(0, splited[0]);
			while (i < ft_count_words(str)) //creer chaque maillon par rapport au nombre d'element de la ligne de commande
			{
				tmp = ft_lstnew(i, splited[i]);
				ft_lstadd_back(&start, tmp);
				i++;
			}
			get_token(start); //debut du lexer qui assigne les token
			check_builtin(start, env); //regarde si il y a builtin dans la ligne de commande et appel les fonction concerner
			tmp = start;
			while (tmp)
			{
				printf("maillon "RED"%d = %s Token = %d\n"END, tmp->value, tmp->str, tmp->token);
				tmp = tmp->next;
			}
			ft_lstclear(start);
		}
	}
}