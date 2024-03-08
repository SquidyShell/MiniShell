/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 23:58:03 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/01 12:14:31 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

size_t	ft_strlen(const char *s);

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	char	*join;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	join = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!join)
		return (NULL);
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	while (s2[i - ft_strlen(s1)])
	{
		join[i] = s2[i - ft_strlen(s1)];
		i++;
	}
	join[i] = 0;
	return (join);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	size_t	i;
	char	*join;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	join = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!join)
		return (NULL);
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	while (s2[i - ft_strlen(s1)])
	{
		join[i] = s2[i - ft_strlen(s1)];
		i++;
	}
	join[i] = 0;
	free(s1);
	free(s2);
	return (join);
}

char	*ft_strjoin_4(char const *s1, char const *s2, char const *s3,
		char const *s4)
{
	int		i;
	char	*join;

	if (!s1 || !s2 || !s3 || !s4)
		return (NULL);
	join = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3)
				+ ft_strlen(s4) + 1));
	if (!join)
		return (NULL);
	i = -1;
	while (s1[++i])
		join[i] = s1[i];
	i--;
	while (s2[++i - ft_strlen(s1)])
		join[i] = s2[i - ft_strlen(s1)];
	i--;
	while (s3[++i - ft_strlen(s1) - ft_strlen(s2)])
		join[i] = s3[i - ft_strlen(s1) - ft_strlen(s2)];
	i--;
	while (s4[++i - ft_strlen(s1) - ft_strlen(s2) - ft_strlen(s3)])
		join[i] = s4[i - ft_strlen(s1) - ft_strlen(s2) - ft_strlen(s3)];
	join[i] = 0;
	return (join);
}

// int	main(int ac, char **av)
// {
// 	if (ac == 3)
// 		printf("strjoin : %s\n", ft_strjoin(av[1], av[2]));
// 	else
// 		printf("ratio");
// 	return (0);
// }
