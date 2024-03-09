/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:46:32 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/09 11:44:43 by cviegas          ###   ########.fr       */
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
	else
	{
		if (*line == '|' && line[1] == '|' && line[2] == '|')
		{
			berr("||");
			exit(1);
		}
	}
	return (0);
}

// void	add_token(t_tokens **tokens, char *line, size_t type, size_t len)
// {
// }

void	parsing(t_tokens **tokens, char *line)
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
		tok_addback(tokens, tok_new(ft_substr(line, 0, len), type));
		line += len;
	}
}
