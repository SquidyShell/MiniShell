/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 07:38:05 by cviegas           #+#    #+#             */
/*   Updated: 2023/12/04 16:36:08 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "first_libft.h"
#include <stdlib.h>
#include <stdio.h>

t_list	*ft_lstnew(void *content);

void	ft_lstadd_back(t_list **lst, t_list *new);

void	ft_lstclear(t_list **lst, void (*del)(void *));

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*map;
	t_list	*checknotnull;

	if (!lst || !f)
		return (NULL);
	map = ft_lstnew(f(lst->content));
	lst = lst->next;
	checknotnull = map;
	while (lst)
	{
		if (!checknotnull)
		{
			ft_lstclear(&map, del);
			return (NULL);
		}
		ft_lstadd_back(&map, ft_lstnew(f(lst->content)));
		checknotnull = map->next;
		lst = lst->next;
	}
	return (map);
}
