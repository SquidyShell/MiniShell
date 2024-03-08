/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:43:13 by cviegas           #+#    #+#             */
/*   Updated: 2023/11/28 05:00:59 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

void	ft_putchar_fd(char c, int fd);

int		ft_putstr_fd(char *s, int fd);

static int	ft_puthexa_fd_aux(unsigned long long hexa, int *print,
	int fd, char *base_16)
{
	if (hexa >= 16)
		ft_puthexa_fd_aux(hexa / 16, print, fd, base_16);
	ft_putchar_fd(base_16[hexa % 16], fd);
	(*print)++;
	return (*print);
}

int	ft_puthexa_min_fd(unsigned long long hexa, int fd)
{
	int	print;

	print = 0;
	return (ft_puthexa_fd_aux(hexa, &print, fd, "0123456789abcdef"));
}

int	ft_puthexa_max_fd(unsigned long long hexa, int fd)
{
	int			print;

	print = 0;
	return (ft_puthexa_fd_aux(hexa, &print, fd, "0123456789ABCDEF"));
}
