/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 21:55:01 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/12 16:21:05 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n - 1 && s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

// int	main(int ac, char **av)
// {
// 	char	*big = "abcdef";
// 	char	*little = "abcdefghijklmnop";

// 	printf("ft_strncmp : %d\n", ft_strncmp(big, little, 6));
// 	printf("strncmp    : %d\n", strncmp(big, little, 6));

// 	if (ac == 4)
// 	{
// 		printf("ft_strncmp : %d\n", ft_strncmp(av[1], av[2], atoi(av[3])));
// 		printf("strncmp    : %d\n", strncmp(av[1], av[2], atoi(av[3])));
// 	}
// }
