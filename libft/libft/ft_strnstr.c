/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 22:13:45 by cviegas           #+#    #+#             */
/*   Updated: 2023/11/14 16:45:47 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

size_t	ft_strlen(const char *s);

int		ft_strncmp(const char *s1, const char *s2, size_t n);

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	if (len == 0 && !big)
		return (NULL);
	if (!little[0] || !little)
		return ((char *)big);
	i = 0;
	while (big[i] && i < len && ft_strlen(little) + i <= len)
	{
		if (!ft_strncmp(&big[i], little, ft_strlen(little)))
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}

// char	*strnstr(const char *big, const char *little, size_t len);

// int	main(int ac, char **av)
// {
// 	char	*s1 = "see FF your FF return FF now FF";
// 	char	*s2 = "FF";

// 	printf("\nft_strnstr : %s\n", ft_strnstr(NULL, "fake", 0));
// 	printf("strnstr   : %s\n\n", strnstr(NULL, "fake", 0));
// 	printf("ft_strnstr : %s\n", ft_strnstr(s1, s2, strlen(s1)));
// 	printf("strnstr    : %s\n", strnstr(s1, s2, strlen(s1)));
// 	if (ac == 4)
// 	{
// 		printf("ft_strnstr : %s\n", ft_strnstr(av[1], av[2], atoi(av[3])));
// 		printf("strnstr    : %s\n", strnstr(av[1], av[2], atoi(av[3])));
// 	}
// }
