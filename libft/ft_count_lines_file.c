/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_lines_file.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablevin <ablevin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:36:24 by ablevin           #+#    #+#             */
/*   Updated: 2023/01/21 14:15:15 by ablevin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_lines_file(char *file_name)
{
	int		fd;
	int		lines;
	int		res_read;
	char	c;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (-1);
	res_read = read(fd, &c, 1);
	if (res_read < 0)
		return (-1);
	else if (res_read == 0)
		return (0);
	lines = 1;
	while (1)
	{
		res_read = read(fd, &c, 1);
		if (res_read < 0)
			return (-1);
		else if (res_read == 0)
			break ;
		if (c == '\n')
			lines++;
	}
	return (close(fd), lines);
}
