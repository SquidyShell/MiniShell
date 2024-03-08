/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min_max.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:21:11 by cviegas           #+#    #+#             */
/*   Updated: 2024/02/02 16:58:46 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_min_max.h"

int	ft_bmin(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	ft_bmax(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	ft_max(int number, ...)
{
	va_list	args;
	int		maximum;
	int		temp;
	int		i;

	if (number <= 0)
		return (-1111111111);
	va_start(args, number);
	maximum = va_arg(args, int);
	i = 1;
	while (i < number)
	{
		temp = va_arg(args, int);
		maximum = ft_bmax(maximum, temp);
		i++;
	}
	va_end(args);
	return (maximum);
}

int	ft_min(int number, ...)
{
	va_list	args;
	int		minimum;
	int		temp;
	int		i;

	if (number <= 0)
		return (-1111111111);
	va_start(args, number);
	minimum = va_arg(args, int);
	i = 1;
	while (i < number)
	{
		temp = va_arg(args, int);
		minimum = ft_bmin(minimum, temp);
		i++;
	}
	va_end(args);
	return (minimum);
}
