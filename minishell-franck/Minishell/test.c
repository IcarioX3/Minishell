/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franck <franck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 02:51:46 by nbled             #+#    #+#             */
/*   Updated: 2023/04/11 14:16:36 by franck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			while (tmp->next)
			{
				printf("maillon "RED"%d = %s "END"token = %d\n", tmp->value, tmp->str, tmp->token);
				tmp = tmp->next;
			}
			printf("maillon "RED"%d = %s "END"token = %d\n", tmp->value, tmp->str, tmp->token);
			ft_lstclear(start);
		}
	}
}
