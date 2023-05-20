/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablevin <ablevin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:03:14 by ablevin           #+#    #+#             */
/*   Updated: 2023/05/20 13:03:15 by ablevin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_nflag(char *input)
{
	int	i;
	int	len;

	i = 1;
	len = 0;
	if (!input)
		return (0);
	if (input[0] != '-')
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

void	ft_echo(char **input, t_blocks *blocks)
{
	int	i;
	int	nflag;

	i = 1;
	nflag = 0;
	if (ft_strlen(input[0]) == 4 && ft_strnstr(input[0], "echo", 4) != NULL)
	{
		if (input[1] != NULL && ft_nflag(input[1]) == 1)
		{
			nflag = 1;
			i++;
		}
		while (i < blocks->nb_args)
		{
			if (input[i] != NULL)
			{
				printf("%s", input[i]);
				if (input[i + 1] != NULL && nflag == 0)
					printf(" ");
			}
			i++;
		}
		if (nflag == 0)
			printf("\n");
	}
}
