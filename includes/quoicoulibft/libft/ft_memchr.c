/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 22:29:31 by cviegas           #+#    #+#             */
/*   Updated: 2023/11/12 19:40:53 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

size_t	ft_strlen(const char *s);

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*temp_s;

	temp_s = (char *)s;
	if (n == 0)
		return (NULL);
	if (c == 0 && n >= ft_strlen(s))
		return ((char *)s + ft_strlen(s));
	i = 0;
	while (i < n)
	{
		if (temp_s[i] == c % 256)
			return ((char *)&temp_s[i]);
		i++;
	}
	return (NULL);
}

// int main()
// {
// 	printf("%c", 't'+256);
// }