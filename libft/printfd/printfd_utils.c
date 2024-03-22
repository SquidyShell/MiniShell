/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printfd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:47:49 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/21 13:15:58 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/first_libft.h"
#include "ft_printfd.h"
#include "limits.h"
#include <stdarg.h>
#include <stdlib.h>

// int	ft_putunsigned_fd_aux(unsigned int n, int fd, int *print)
// {
// 	if (n != 0)
// 	{
// 		(*print)++;
// 		ft_putunsigned_fd_aux(n / 10, fd, print);
// 		ft_putchar_fd(n % 10 + '0', fd);
// 	}
// 	return (*print);
// }

// int	ft_putunsigned_fd(unsigned int n, int fd)
// {
// 	int nb_printed;

// 	nb_printed = 0;
// 	if (n == 0)
// 		return (ft_putchar_fd('0', fd), 1);
// 	nb_printed = ft_putunsigned_fd_aux(n, fd, &nb_printed);
// 	return (nb_printed);
// }

// int	ft_putunsigned_fd_aux(unsigned int n, int fd, int *print)
// {
// 	if (n != 0)
// 	{
// 		(*print)++;
// 		ft_putunsigned_fd_aux(n / 10, fd, print);
// 		ft_putchar_fd(n % 10 + '0', fd);
// 	}
// 	return (*print);

static size_t	count_sizet_aux(size_t u_nb, size_t *count)
{
	if (u_nb != 0)
	{
		(*count)++;
		count_sizet_aux(u_nb / 10, count);
	}
	return (*count);
}

size_t	count_print_sizet(size_t u_nb)
{
	size_t	count;

	count = 0;
	if (u_nb == 0)
		return (1);
	return (count_sizet_aux(u_nb, &count));
}

void	fill_in_sizet_aux(char *buffer, size_t u_nb, size_t *i)
{
	if (u_nb >= 10)
	{
		fill_in_sizet_aux(buffer, u_nb / 10, i);
	}
	buffer[(*i)++] = (u_nb % 10) + '0';
}

void	fill_in_sizet(char *buffer, size_t u_nb)
{
	size_t	i;

	if (u_nb == 0)
	{
		buffer[0] = '0';
		buffer[1] = '\0';
		return ;
	}
	i = 0;
	fill_in_sizet_aux(buffer, u_nb, &i);
	buffer[i + 1] = '\0';
}
