/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 21:27:32 by cviegas           #+#    #+#             */
/*   Updated: 2023/11/12 19:45:16 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

size_t	ft_strlen(const char *s);

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	if (c == 0)
		return ((char *)s + ft_strlen(s));
	i = ft_strlen(s) - 1;
	while (i >= 0)
	{
		if (s[i] == c % 256)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}

// int	main(int ac, char **av)
// {
// 	if (ac == 3)
// 	{
// 		printf("ft_strrchr : %s\n", ft_strrchr(av[1], *av[2]));
// 		printf("strrchr    : %s\n", strrchr(av[1], *av[2]));
// 	}
// }
