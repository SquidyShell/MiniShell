/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 04:44:26 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/20 11:12:17 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "first_libft.h"
#include <stdio.h>
#include <stdlib.h>

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
		(i++, lst = lst->next);
	return (i);
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

// void	ft_lstadd_front(t_list **lst, t_list *new);

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
// 	printf("%d", ft_lstsize(squid));
// }
