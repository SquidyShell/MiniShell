/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:54:38 by cviegas           #+#    #+#             */
/*   Updated: 2024/02/02 19:03:38 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "first_libft.h"
#include "stdlib.h"

// Creates a String (char *) with all whitespaces
// (to use it with split charset after)
char	*str_whitespaces(void)
{
	char	*whitespaces;
	size_t	i;

	whitespaces = malloc(sizeof(char) * 7);
	if (!whitespaces)
		return (NULL);
	i = 0;
	while (i < 5)
	{
		whitespaces[i] = i + 9;
		i++;
	}
	whitespaces[i++] = ' ';
	whitespaces[i] = 0;
	return (whitespaces);
}

// Frees a char **
void	free_s(char **s)
{
	size_t	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}
