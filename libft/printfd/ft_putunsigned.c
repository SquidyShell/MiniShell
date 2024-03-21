/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:43:13 by cviegas           #+#    #+#             */
/*   Updated: 2023/12/03 20:03:22 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

void	ft_putchar_fd(char c, int fd);

int	ft_putunsigned_fd_aux(unsigned int n, int fd, int *print)
{
	if (n != 0)
	{
		(*print)++;
		ft_putunsigned_fd_aux(n / 10, fd, print);
		ft_putchar_fd(n % 10 + '0', fd);
	}
	return (*print);
}

int	ft_putunsigned_fd(unsigned int n, int fd)
{
	int	nb_printed;

	nb_printed = 0;
	if (n == 0)
		return (ft_putchar_fd('0', fd), 1);
	nb_printed = ft_putunsigned_fd_aux(n, fd, &nb_printed);
	return (nb_printed);
}

// int	main(int ac, char **av)
// {
// 	ac = 0;
// 	printf("putunsigned : ");
// 	printf("\nNombre de char ecrits : %u\n",ft_putunsigned_fd(atoi(av[1]), 1));
// }
