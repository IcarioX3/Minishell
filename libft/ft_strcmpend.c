/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmpend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablevin <ablevin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:23:28 by icario            #+#    #+#             */
/*   Updated: 2023/01/20 13:14:47 by ablevin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmpend(char *str, char *end)
{
	int	lenstr;
	int	lenend;

	lenstr = ft_strlen(str);
	lenend = ft_strlen(end);
	if (!str || !end || lenstr < lenend)
		return (0);
	while (lenend > 0)
	{
		if (end[lenend - 1] != str[lenstr - 1])
			return (0);
		lenend--;
		lenstr--;
	}
	return (1);
}
/*
int	main(void)
{
	ft_printf("%d\n", ft_strcmpend("map.ber", ".ber"));
}*/
