/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:29:12 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/11 11:47:00 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	check_quotes(char *line)
{
	bool	in_dquote;
	bool	in_quote;

	in_dquote = 0;
	in_quote = 0;
	while (*line)
	{
		if (!in_quote && !in_dquote && *line == '\'')
			in_quote = 1;
		if (in_quote && *line == '\'')
			in_quote = 0;
		if (!in_quote && !in_dquote && *line == '\"')
			in_dquote = 1;
		if (in_dquote && *line == '\"')
			in_dquote = 0;
		*line++;
	}
	if (in_dquote)
		return (printfd(STDERR,
				"🦑: unexpected EOF while looking for matching `%s%s%s'\n%s",
				PINK, "'", RESET, "🦑: syntax error: unexpected end of file"),
			0);
	if (in_quote)
		return (printfd(STDERR,
				"🦑: unexpected EOF while looking for matching `%s%s%s'\n%s",
				PINK, "\"", RESET, "🦑: syntax error: unexpected end of file"),
				0);
	return (1);
}

bool	is_syntax_correct(char *line)
{
	if (!check_quotes(line))
		return (0);
	return (1);
}
