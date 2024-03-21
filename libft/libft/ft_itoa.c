/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 04:10:22 by cviegas           #+#    #+#             */
/*   Updated: 2023/11/12 22:00:32 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

size_t	ft_strlen(const char *s);

static char	*strrev(char *s)
{
	int		i;
	int		j;
	char	temp;

	if (s[0] == '-')
		i = 1;
	else
		i = 0;
	j = ft_strlen(s) - 1;
	while (i < j)
	{
		temp = s[j];
		s[j] = s[i];
		s[i] = temp;
		i++;
		j--;
	}
	return (s);
}

static int	itoa_size(long int n)
{
	int	i;

	i = 0;
	if (n <= 0)
	{
		i++;
		n *= -1;
	}
	while (n > 0)
	{
		i++;
		n /= 10;
	}
	return (i + 1);
}

char	*ft_itoa(int n)
{
	char		*itoa;
	int			i;
	long int	long_n;

	long_n = n;
	i = 0;
	itoa = malloc(itoa_size(long_n) * sizeof(char));
	if (!itoa)
		return (NULL);
	if (long_n == 0)
		itoa[i++] = '0';
	if (long_n < 0)
	{
		itoa[i++] = '-';
		long_n *= -1;
	}
	while (long_n > 0)
	{
		itoa[i++] = long_n % 10 + '0';
		long_n /= 10;
	}
	itoa[i] = 0;
	return ((strrev(itoa)));
}

// int	main(int ac, char **av)
// {
// 	if (ac == 2)
// 	{
// 		printf("%s", ft_itoa(atoi(av[1])));
// 	}
// }
