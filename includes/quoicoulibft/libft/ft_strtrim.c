/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 00:34:58 by cviegas           #+#    #+#             */
/*   Updated: 2023/11/11 19:29:36 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

size_t	ft_strlen(const char *s);

char	*ft_substr(char const *s, unsigned int start, size_t len);

static int	is_inset(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*trim;

	if (!s1)
		return (NULL);
	start = 0;
	while (is_inset(s1[start], set) && s1[start])
		start++;
	end = ft_strlen(s1) - 1;
	while (is_inset(s1[end], set) && end > start)
		end--;
	trim = ft_substr(s1, start, end - start + 1);
	return (trim);
}

// int	main(int ac, char **av)
// {
// 	if (ac == 3)
// 	{
// 		printf("ft_strtrim : %s", ft_strtrim(av[1],av[2]));
// 	}
// }
