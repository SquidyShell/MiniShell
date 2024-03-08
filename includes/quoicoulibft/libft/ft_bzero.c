/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:09:26 by cviegas           #+#    #+#             */
/*   Updated: 2023/11/12 19:39:42 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	*ft_memset(void *s, int c, size_t n);

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

// int main(int ac, char **av)
// {
// 	if (ac == 4)
// 	{
// 		printf("\n---- bzero ----\n");
// 		char str_bzero[100];
// 		char str_ft_bzero[100];
// 		strcpy(str_bzero, av[1]);
// 		strcpy(str_ft_bzero, av[1]);
// 		bzero(str_bzero + atoi(av[3]), atoi(av[2]));
// 		ft_bzero(str_ft_bzero + atoi(av[3]), atoi(av[2]));
// 		printf("ft_bzero : %s\n", str_ft_bzero);
// 		printf("bzero    : %s\n", str_bzero);
// 	}
// }