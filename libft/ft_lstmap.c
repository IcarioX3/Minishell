/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icario <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 16:35:59 by icario            #+#    #+#             */
/*   Updated: 2022/06/23 18:13:35 by icario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lstnew;
	t_list	*first;

	if (!lst || !f || !del)
		return (NULL);
	lstnew = ft_lstnew(f(lst->content));
	if (!lstnew)
		return (NULL);
	first = lstnew;
	lst = lst->next;
	while (lst)
	{
		lstnew->next = ft_lstnew(f(lst->content));
		if (lstnew->next == NULL)
		{
			ft_lstclear(&first, del);
			return (NULL);
		}
		lstnew = lstnew->next;
		lst = lst->next;
	}
	return (first);
}
