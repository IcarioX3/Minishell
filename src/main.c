/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frgojard <frgojard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:54:00 by icario            #+#    #+#             */
/*   Updated: 2023/04/03 16:34:29 by frgojard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;

	char	*cmd;
	while (1)
	{
		cmd = readline(BLUE"minishell :"END);
		if (!cmd)
			break ;
		add_history(cmd);
	}
}
