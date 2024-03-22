/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:34:08 by cviegas           #+#    #+#             */
/*   Updated: 2023/11/11 19:56:50 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*temp_dest;
	char	*temp_src;

	if (!src && !dest)
		return (NULL);
	temp_dest = (char *)dest;
	temp_src = (char *)src;
	i = 0;
	while (i < n)
	{
		temp_dest[i] = temp_src[i];
		i++;
	}
	return (dest);
}

// int	main(int ac, char **av)
// {
// 	if (ac == 4)
// 	{
// 		printf("\n---- memcpy ----\n");
// 		char squidgame[50];
// 		char squidgame2[50];
// 		char str_memcpy[100];
// 		char str_ft_memcpy[100];
// 		strcpy(squidgame, "squidgame");
// 		strcpy(squidgame2, "squidgame");
// 		strcpy(str_memcpy, av[1]);
// 		strcpy(str_ft_memcpy, av[1]);
// 		memcpy(squidgame + 1, squidgame, atoi(av[3]));
// 		ft_memcpy(squidgame2 + 1, squidgame2, atoi(av[3]));
// 		printf("memcpy    : %s\n", squidgame);
// 		printf("ft_memcpy : %s\n", squidgame2);
// 	}
// }