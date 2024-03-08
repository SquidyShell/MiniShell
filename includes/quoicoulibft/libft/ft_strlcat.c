/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 20:48:24 by cviegas           #+#    #+#             */
/*   Updated: 2023/11/16 19:32:15 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

size_t	ft_strlen(const char *s);

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dlen;

	if (!dst && size == 0)
		return (0);
	dlen = ft_strlen(dst);
	if (size <= dlen)
		return (size + ft_strlen(src));
	i = 0;
	while (src[i] && (dlen + i + 1) < size)
	{
		dst[i + dlen] = src[i];
		i++;
	}
	dst[i + dlen] = 0;
	return (dlen + ft_strlen(src));
}

// size_t	strlcat(char *dst, const char *src, size_t size);

// int	main(int ac, char **av)
// {
// 	if (ac == 4)
// 	{
// 		printf("ft_strlcat  %zu\n", ft_strlcat(av[1], av[2], atoi(av[3])));
// 		printf("strlcat     %zu\n", strlcat(av[1], av[2], atoi(av[3])));
// 	}
// 	else
// 	{
// 		printf("ratio");
// 	}
// 	return (0);
// }