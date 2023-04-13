/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablevin <ablevin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:20:12 by ablevin           #+#    #+#             */
/*   Updated: 2023/04/13 11:20:15 by ablevin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strinsert(char *str, char *insert, int index)
{
	char	*new;
	int		i;
	int		j;
	int		len;

	len = ft_strlen(str) + ft_strlen(insert) + 1;
	new = (char *)malloc(sizeof(char) * len);
	if (new == NULL)
		return (NULL);
	i = -1;
	while (++i < index && str[i])
		new[i] = str[i];
	j = -1;
	while (insert[++j])
		new[i + j] = insert[j];
	while (str[i])
	{
		new[i + j] = str[i];
		i++;
	}
	new[i + j] = '\0';
	return (new);
}
/*
int	main(void)
{
	char	str[50] = "Hello, world!";
	char	insert[10] = "beautiful";
	int		index = 7;
	char	*result;

	printf("Before: %s\n", str);
	result = ft_strinsert(str, insert, index);
	if (result == NULL)
	{
		fprintf(stderr, "Error: failed to allocate memory\n");
		return (1);
	}
	printf("After: %s\n", result);
	free(result);
	return (0);
}*/
