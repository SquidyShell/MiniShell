/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:17:09 by cviegas           #+#    #+#             */
/*   Updated: 2023/11/14 16:16:58 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <stdint.h>

void	ft_bzero(void *s, size_t n);

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*array;

	if (nmemb * size == 0)
	{
		array = malloc(0);
		if (!array)
			return (NULL);
		return (array);
	}
	if (nmemb * size / nmemb != size || nmemb * size / size != nmemb)
		return (NULL);
	array = malloc(nmemb * size);
	if (!array)
		return (NULL);
	ft_bzero(array, nmemb * size);
	return (array);
}

// int	main(void)
// {

// 	ft_calloc(4, 4);
// }
