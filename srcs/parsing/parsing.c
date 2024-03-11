/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:46:32 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/11 05:29:01 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	is_symbol(char c)
{
	if (c == '|' || c == '&' || c == '<' || c == '>')
		return (1);
	return (0);
}

bool	is_whitespace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

size_t	search_for_lenght(char *line, size_t *len, size_t type)
{
	size_t	i;

	i = 0;
	if (type == WORD)
		while (line[i] && !is_whitespace(line[i]) && !is_symbol(line[i]))
			i++;
	*len = i;
	return (type);
}

int	get_type_and_len(char *line, size_t *len)
{
	if (!is_symbol(*line))
		return (search_for_lenght(line, len, WORD));
	else if (*line == '|')
		return (search_for_lenght(line, len, PIPE));
	return (0);
}

void	parsing(t_vars *vars, char *line)
{
	size_t	type;
	size_t	len;

	while (*line)
	{
		while (is_whitespace(*line))
			line++;
		if (!*line)
			break ;
		type = get_type_and_len(line, &len);
		tok_addback(vars, tok_new(ft_substr(line, 0, len), type));
		line += len;
	}
}
