/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 00:24:30 by cviegas           #+#    #+#             */
/*   Updated: 2023/11/11 05:30:58 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	ft_atoi(const char *nptr)
{
	int	i;
	int	atoi;
	int	indice;

	i = 0;
	atoi = 0;
	indice = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '+')
		i++;
	else if (nptr[i] == '-')
	{
		indice = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		atoi *= 10;
		atoi += nptr[i] - '0';
		i++;
	}
	return (atoi * indice);
}

// int	main(int ac, char **av)
// {
// 	if (ac == 2)
// 	{
// 		printf("ft_atoi : %d\n", ft_atoi(av[1]));
// 		printf("atoi    : %d", atoi(av[1]));
// 	}
// }
