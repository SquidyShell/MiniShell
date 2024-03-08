/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:52:00 by cviegas           #+#    #+#             */
/*   Updated: 2023/11/08 13:54:27 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*p;

	i = 0;
	p = (char *)s;
	while (i < n)
	{
		p[i] = c;
		i++;
	}
	return (s);
}

// int main(int ac, char **av)
// {
// 	if (ac == 4)
// 	{
// 		printf("\n---- memset ----\n");
// 		char str_memset[strlen(av[1])];
// 		strcpy(str_memset, av[1]);
// 		memset(str_memset, *av[2], atoi(av[3]));
// 		char str_ft[strlen(av[1])];
// 		strcpy(str_ft, av[1]);
// 		ft_memset(str_ft, *av[2], atoi(av[3]));
// 		printf("ft_memset : %s\n", str_ft);
// 		printf("memset    : %s\n", str_memset);
// 	}
// }
