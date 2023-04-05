/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablevin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:37:10 by ablevin           #+#    #+#             */
/*   Updated: 2022/05/31 16:36:55 by ablevin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const char	*s;
	char		*d;
	const char	*lasts;
	char		*lastd;

	if (!dest && !src)
		return (NULL);
	s = src;
	d = dest;
	lasts = s + (n - 1);
	lastd = d + (n - 1);
	if (d < s)
		while (n--)
			*d++ = *s++;
	else
		while (n--)
			*lastd-- = *lasts--;
	return (dest);
}
