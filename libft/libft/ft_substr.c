/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 23:14:04 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/22 16:06:23 by cviegas          ###   ########.fr       */
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

/* ft_substr but skips the "to_skip" char passed by argument */
char	*substr_s(char const *s, size_t start, size_t len, char to_skip)
{
	char	*substr;
	size_t	i;
	size_t	j;

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
	j = 0;
	while (j < len && s[j + start])
	{
		if (s[j + start] != to_skip)
			substr[i++] = s[j + start];
		j++;
	}
	substr[i] = 0;
	return (substr);
}

/* ft_substr but skips the "to_skip" char passed by argument */
char	*substr_2s(char const *s, size_t start, size_t len, char to_skip[2])
{
	char	*substr;
	size_t	i;
	size_t	j;

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
	j = 0;
	while (j < len && s[j + start])
	{
		if (s[j + start] != to_skip[0] && s[j + start] != to_skip[1])
			substr[i++] = s[j + start];
		j++;
	}
	substr[i] = 0;
	return (substr);
}

// int	main(int ac, char **av)
// {
// 	char *str;

// 	if (ac == 5)
// 	{
// 		str = ft_substr_skip(av[1], atoi(av[2]), atoi(av[3]), av[4][0]);
// 		printf("ft_substr_skip : %s\n", str);
// 		free(str);
// 	}
// 	else
// 		printf("ratio");
// 	return (0);
// }