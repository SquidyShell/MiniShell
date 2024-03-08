/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 05:17:29 by cviegas           #+#    #+#             */
/*   Updated: 2024/01/12 22:20:50 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "first_libft.h"
#include <stdio.h>
#include <stdlib.h>

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;
	t_list	*next;

	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	current = *lst;
	next = *lst;
	while (next)
	{
		current = next;
		next = current->next;
	}
	current->next = new;
}

void	print_t_list(t_list *lst)
{
	while (lst)
	{
		printf("%s -> ", (char *)lst->content);
		lst = lst->next;
	}
	printf("NULL\n");
}

// t_list	*ft_lstnew(void *content);

// int	main(int ac, char **av)
// {
// 	t_list	*squid;
// 	t_list	*game;
// 	int		i;

// 	i = 2;
// 	squid = ft_lstnew(av[1]);
// 	while (i <= ac)
// 	{
// 		ft_lstadd_back(&squid, ft_lstnew(av[i]));
// 		i++;
// 	}
// 	ac = 0;
// 	squid = ft_lstnew(av[1]);
// 	ft_lstadd_back(&squid, ft_lstnew(av[2]));
// 	print_t_list(squid);
// 	game = ft_lstnew(av[3]);
// 	ft_lstadd_back(&game, ft_lstnew(av[4]));
// 	ft_lstadd_back(&squid, game);
// 	print_t_list(squid);
// }
