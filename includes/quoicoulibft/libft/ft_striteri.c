/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 19:57:30 by cviegas           #+#    #+#             */
/*   Updated: 2023/11/12 20:18:14 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

// void	print_index_char(unsigned int i, char *c)
// {
// 	printf("%d: %c\n", i, *c);
// }

// void	ft_squidgame(unsigned int i, char *c)
// {
// 	char	*squidgame = "Squid Game";

// 	*c = squidgame[i % 11];
// }

// int	main(int ac, char **av)
// {
// 	if (ac == 2)
// 	{
// 		ft_striteri(av[1], &print_index_char);
// 		printf("\n");
// 		ft_striteri(av[1], &ft_squidgame);
// 		printf("\n");
// 		ft_striteri(av[1], &print_index_char);
// 	}
// 	else
// 		printf("ratio");
// }
