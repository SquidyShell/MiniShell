/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 06:52:27 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/20 13:57:24 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "first_libft.h"
#include <stdio.h>
#include <stdlib.h>

// static void	s(void)
// {
// 	dprintf(2, "%s%sSQUID%s\n", "\033[1m", "\033[32m", "\033[0m");
// }

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next;

	if (!lst)
		return ;
	while (*lst)
	{
		next = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = next;
	}
}

void	ft_lstclear_no_free(t_list **lst)
{
	t_list	*current;
	t_list	*next;

	if (!lst)
		return ;
	current = *lst;
	next = *lst;
	while (next)
	{
		current = next;
		next = current->next;
		free(current);
	}
	*lst = NULL;
}
