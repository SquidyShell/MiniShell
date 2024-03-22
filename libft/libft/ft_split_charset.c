/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_charset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:37:54 by cviegas           #+#    #+#             */
/*   Updated: 2024/01/13 19:15:54 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "first_libft.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	init_ints(int *k, int *j)
{
	*k = 0;
	*j = 0;
}

static char	**free_splitted(char ***split)
{
	int	i;

	i = 0;
	while (*split[i])
		free(*split[i++]);
	free(*split);
	return (NULL);
}

char	*create_string(const char *str, char *charset, int *j)
{
	char	*new_str;
	int		i;

	new_str = ft_calloc((lenbsep(str, charset, *j) + 1), 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while (lenbsep(str, charset, *j) > 0)
		new_str[i++] = str[(*j)++];
	(*j)--;
	return (new_str);
}

char	**ft_split_charset(const char *str, char *charset)
{
	char	**ret;
	int		j;
	int		k;

	if (!str)
		return (if_str_null(str));
	ret = ft_calloc(sizeof(char *) * (ft_nb_mots(str, charset) + 1), 1);
	if (!ret)
		return (NULL);
	init_ints(&k, &j);
	while (str[j])
	{
		if (lenbsep(str, charset, j) > 0)
		{
			ret[k] = create_string(str, charset, &j);
			if (!ret[k++])
				return (free_splitted(&ret));
		}
		j++;
	}
	ret[k] = NULL;
	return (ret);
}

// void	afficherTableauStrings(char **tableau)
// {
// 	int	i;

// 	i = 0;
// 	while (tableau[i])
// 	{
// 		printf("%s\n", tableau[i]);
// 		i++;
// 	}
// }

// void	free_splitter(char **s)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		free(s[i]);
// 		i++;
// 	}
// 	free(s);
// }

// int	main(int ac, char **av)
// {
// 	if (ac != 3)
// 		printf("Erreur");
// 	else
// 	{
// 		char **squid = ft_split_charset(av[1], av[2]);
// 		afficherTableauStrings(squid);
// 		free_splitter(squid);
// 	}
// 	return (0);
// }