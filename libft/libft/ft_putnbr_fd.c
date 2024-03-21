/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 05:57:36 by cviegas           #+#    #+#             */
/*   Updated: 2023/11/18 02:56:41 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

void	ft_putchar_fd(char c, int fd);

void	ft_put_solo_str(char *s, int fd)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

int	ft_putnbr_fd_aux(int n, int fd, int *print)
{
	if (n > 0)
	{
		(*print)++;
		ft_putnbr_fd_aux(n / 10, fd, print);
		ft_putchar_fd(n % 10 + '0', fd);
	}
	return (*print);
}

int	ft_putnbr_fd(int n, int fd)
{
	int	nb_printed;

	nb_printed = 0;
	if (n == -2147483648)
		return (ft_put_solo_str("-2147483648", fd), 11);
	else if (n == 0)
		return (ft_putchar_fd('0', fd), 1);
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		nb_printed++;
		n *= -1;
	}
	nb_printed = ft_putnbr_fd_aux(n, fd, &nb_printed);
	return (nb_printed);
}

// int	main(int ac, char **av)
// {
// 	ac = 0;
// 	printf("putnbr : ");
// 	printf("\nNombre de char ecrits : %d\n",ft_putnbr_fd(atoi(av[1]), 1));
// }
