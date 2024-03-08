/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_charset_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 18:08:48 by cviegas           #+#    #+#             */
/*   Updated: 2024/01/13 18:49:24 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "first_libft.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	is_sep(const char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

int	lenbsep(const char *s, char *charset, int indice_s)
{
	int	i;

	i = 0;
	while (!is_sep(s[indice_s], charset) && s[indice_s])
	{
		indice_s++;
		i++;
	}
	return (i);
}

int	ft_nb_mots(const char *str, char *charset)
{
	int	i;
	int	nb_mots;

	i = 0;
	nb_mots = 0;
	while (str[i])
	{
		if (is_sep(str[i], charset))
			nb_mots++;
		i++;
	}
	return (nb_mots + 1);
}

char	**if_str_null(const char *str)
{
	char	**ret;

	ret = malloc(sizeof(char *) * 2);
	ret[0] = ft_strdup(str);
	ret[1] = 0;
	return (ret);
}
