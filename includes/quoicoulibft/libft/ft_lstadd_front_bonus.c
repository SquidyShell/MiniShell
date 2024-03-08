/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 23:36:20 by cviegas           #+#    #+#             */
/*   Updated: 2023/12/04 16:35:51 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "first_libft.h"
#include <stdlib.h>
#include <stdio.h>

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

// void	print_t_list(t_list *lst)
// {
// 	while (lst)
// 	{
// 		printf("%s -> ", (char *)lst->content);
// 		lst = lst->next;
// 	}
// 	printf("NULL\n");
// }

// t_list	*ft_lstnew(void *content);

// int	main(int ac, char **av)
// {
// 	t_list	*squid;
// 	t_list	*new;

// 	ac = 0;
// 	squid = ft_lstnew(av[1]);
// 	print_t_list(squid);
// 	new = ft_lstnew(av[2]);
// 	ft_lstadd_front(&squid, new);
// 	print_t_list(squid);
// }
