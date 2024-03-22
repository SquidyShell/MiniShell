/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 00:52:52 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/20 13:49:40 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int	size_until_sep(char const *s, char sep, int indice)
{
	int	size;

	size = 0;
	while (s[indice] && s[indice] != sep)
	{
		indice++;
		size++;
	}
	return (size);
}

static int	nb_words(char const *s, char c)
{
	int	i;
	int	word;

	i = 0;
	while (s[i] == c && s[i])
		i++;
	word = 0;
	while (s[i])
	{
		while (s[i] != c && s[i])
			i++;
		word++;
		while (s[i] == c && s[i])
			i++;
	}
	return (word);
}

int	skip_sep(int i, char c, char const *s)
{
	while (s[i] == c && s[i])
		i++;
	return (i);
}

void	free_splitted(char **t)
{
	size_t	i;

	if (!t)
		return ;
	i = 0;
	while (t[i])
		free(t[i++]);
	free(t);
	t = NULL;
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		word;
	char	**splitted;

	if (!s)
		return (NULL);
	splitted = malloc(sizeof(char *) * (nb_words(s, c) + 1));
	if (!splitted)
		return (NULL);
	i = skip_sep(0, c, s);
	word = 0;
	while (s[i])
	{
		j = 0;
		splitted[word] = malloc((size_until_sep(s, c, i) + 1) * sizeof(char));
		if (!splitted[word])
			return (free_splitted(splitted), NULL);
		while (s[i] != c && s[i])
			splitted[word][j++] = s[i++];
		splitted[word++][j] = 0;
		i = skip_sep(i, c, s);
	}
	splitted[word] = NULL;
	return (splitted);
}

// void	aff_split(char **split)
// {
// 	int	i;

// 	i = 0;
// 	while (split[i])
// 	{
// 		printf("%s\n", split[i]);
// 		i++;
// 	}
// }

// int	main(int ac, char **av)
// {
// 	ac = 0;
// 	aff_split(ft_split(av[1], 'c'));
// }
