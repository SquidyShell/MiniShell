/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:34:08 by cviegas           #+#    #+#             */
/*   Updated: 2023/11/13 04:04:36 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*temp_dest;
	char	*temp_src;

	if (!src && !dest)
		return (NULL);
	temp_dest = (char *)dest;
	temp_src = (char *)src;
	if (temp_dest < temp_src)
	{
		i = 0;
		while (i < n)
		{
			temp_dest[i] = temp_src[i];
			i++;
		}
		return (dest);
	}
	i = n;
	while (i > 0)
	{
		i--;
		temp_dest[i] = temp_src[i];
	}
	return (dest);
}

// int	main(int ac, char **av)
// {
// 	if (ac == 4)
// 	{
// 		printf("\n---- memmove ----\n");
// 		char str_memmove[100];
// 		char str_ft_memmove[100];
// 		strcpy(str_memmove, av[1]);
// 		strcpy(str_ft_memmove, av[1]);
// 		memmove(str_memmove, av[2], atoi(av[3]));
// 		ft_memmove(str_ft_memmove, av[2], atoi(av[3]));
// 		printf("memmove    : %s\n", str_memmove);
// 		printf("ft_memmove : %s\n", str_ft_memmove);
// 	}
// }