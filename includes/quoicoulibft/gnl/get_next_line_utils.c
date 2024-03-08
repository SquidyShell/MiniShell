/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:45:32 by cviegas           #+#    #+#             */
/*   Updated: 2023/12/19 03:11:59 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

// Renvoie le nombre total de caracteres de toutes les chaines de 
// caracteres contenues dans la liste chainee.
int	size_of_stash(t_list *stash)
{
	char	*content;
	int		size;
	int		i;

	size = 0;
	while (stash)
	{
		content = stash->content;
		i = 0;
		while (content[i])
		{
			i++;
			size++;
		}
		stash = stash->next;
	}
	return (size);
}

// Renvoie un string a partir de toutes les strings de la t_list
// C'est une sorte de strjoin de toutes les strings contenues dans la stash
char	*stash_to_line(t_list *stash)
{
	char	*line;
	char	*content;
	int		i;
	int		j;

	line = malloc(sizeof(char) * (size_of_stash(stash) + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (stash)
	{
		content = stash->content;
		j = 0;
		while (content[j])
			line[i++] = content[j++];
		stash = stash->next;
	}
	line[i] = 0;
	return (line);
}
