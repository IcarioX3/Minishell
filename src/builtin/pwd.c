/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablevin <ablevin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:03:29 by ablevin           #+#    #+#             */
/*   Updated: 2023/05/20 13:03:30 by ablevin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(char **input)
{
	char	cwd[4096];

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
				perror("Error during call of getcwd()");
				return (1);
			}
		}
	}
	return (0);
}
