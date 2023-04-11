/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 08:19:28 by nbled             #+#    #+#             */
/*   Updated: 2023/02/23 08:19:30 by nbled            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstadd_back(t_pile **pile, t_pile *n)
{
	t_pile	*ptr;

	if (!pile || !n)
		return ;
	if (!(*pile))
	{
		*pile = n;
		return ;
	}
	ptr = *pile;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = n;
	n->prev = ptr;
}
