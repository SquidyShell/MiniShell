/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 23:14:04 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/11 17:23:14 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

size_t		ft_strlen(const char *s);

static char	*create_null_char(void)
{
	char	*substr;

	substr = malloc(sizeof(char));
	if (!substr)
		return (NULL);
	substr[0] = 0;
	return (substr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	if (start >= ft_strlen(s))
		return (create_null_char());
	while (i < len && s[i + start])
		i++;
	substr = malloc((i + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len && s[i + start])
	{
		substr[i] = s[i + start];
		i++;
	}
	substr[i] = 0;
	return (substr);
}

// char	*ft_substr_skip(char const *s, size_t start, size_t len, char to_skip)
// {
// 	char	*substr;
// 	size_t	i;
// 	size_t	j;

// 	if (!s)
// 		return (NULL);
// 	i = 0;
// 	if (start >= ft_strlen(s))
// 		return (create_null_char());
// 	while (i < len && s[i + start])
// 		i++;
// 	substr = malloc((i + 1) * sizeof(char));
// 	if (!substr)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	while (i < len && s[j + start])
// 	{
// 		if (s[j + start] != to_skip)
// 		substr[i] = s[j + start];
// 		i++;
// 	}
// 	substr[i] = 0;
// 	return (substr);
// }

// int	main(int ac, char **av)
// {
// 	if (ac == 4)
// 	{
// 		printf("ft_substr : %s\n", ft_substr(av[1], atoi(av[2]), atoi(av[3])));
// 	}
// 	else
// 		printf("ratio");
// 	return (0);
// }