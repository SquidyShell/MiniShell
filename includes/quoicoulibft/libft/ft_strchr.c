/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 21:27:32 by cviegas           #+#    #+#             */
/*   Updated: 2023/11/12 19:44:20 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

size_t	ft_strlen(const char *s);

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (c == 0)
		return ((char *)s + ft_strlen(s));
	while (s[i])
	{
		if (s[i] == c % 256)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}

// int	main(int ac, char **av)
// {
// 	if (ac == 3)
// 	{
// 		printf("ft_strchr : %s\n", ft_strchr(av[1], *av[2]));
// 		printf("strchr    : %s\n", strchr(av[1], *av[2]));
// 	}
// }
