/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablevin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:13:33 by ablevin           #+#    #+#             */
/*   Updated: 2022/05/31 17:13:37 by ablevin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"

char	*ft_strrchr(char *s, int c)
{
	int	len;
	int	i;

	len = ft_strlen(s);
	i = 0;
	while (i < len + 1)
	{
		if (s[len - i] == (unsigned char) c)
			return ((char *)(s + len - i));
		i++;
	}
	return (NULL);
}
/*
int	main(void)
{
	printf("%s\n", ft_strrchr("tripouille", 't' + 256));
	printf("%s\n", strrchr("tripouille", 't' + 256));
	return (0);
}*/
