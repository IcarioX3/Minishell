/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icario <icario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 11:57:34 by ablevin           #+#    #+#             */
/*   Updated: 2023/01/19 11:20:17 by icario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(int nmemb, int size)
{
	void	*dest;

	if (nmemb && (nmemb * size / nmemb) != size)
		return (0);
	dest = malloc(nmemb * size);
	if (!dest)
		return (0);
	ft_bzero(dest, (nmemb * size));
	return (dest);
}
