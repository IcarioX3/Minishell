/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablevin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:16:40 by ablevin           #+#    #+#             */
/*   Updated: 2022/06/08 15:57:36 by ablevin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst)
		return ;
	new->next = *lst;
	*lst = new;
}
/*
int	main(void)
{
	t_list	*list;
	list = ft_lstnew("hello");
	ft_lstadd_front(&list, ft_lstnew("world"));
	while (list != NULL)
	{
		printf("%s", (char *)list->content);
		list = list->next;
	}
	return (0);
}*/