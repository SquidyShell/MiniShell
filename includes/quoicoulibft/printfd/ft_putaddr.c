/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:43:13 by cviegas           #+#    #+#             */
/*   Updated: 2023/12/15 22:54:31 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void		ft_putchar_fd(char c, int fd);

int			ft_putstr_fd(char *s, int fd);

static int	ft_putaddr_fd_aux(unsigned long long addr, int *print, int fd)
{
	char	*base_16;

	base_16 = "0123456789abcdef";
	if (addr >= 16)
		ft_putaddr_fd_aux(addr / 16, print, fd);
	ft_putchar_fd(base_16[addr % 16], fd);
	(*print)++;
	return (*print);
}

int	ft_putaddr_fd(void *addr, int fd)
{
	int					print;
	unsigned long long	hexa;

	if (!addr)
	{
		ft_putstr_fd("(nil)", fd);
		return (5);
	}
	hexa = (unsigned long long)addr;
	ft_putstr_fd("0x", fd);
	print = 2;
	return (ft_putaddr_fd_aux(hexa, &print, fd));
}

// int	main(int ac, char **av)
// {
// 	ac = 0;
// 	printf("putunsigned : ");
// 	printf("\nNombre de char ecrits : %u\n",ft_putunsigned_fd(atoi(av[1]), 1));
// }
