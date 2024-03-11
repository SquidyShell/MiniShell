/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:29:12 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/11 19:23:48 by cviegas          ###   ########.fr       */
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
		else if (in_quote && *line == '\'')
			in_quote = 0;
		if (!in_quote && !in_dquote && *line == '\"')
			in_dquote = 1;
		else if (in_dquote && *line == '\"')
			in_dquote = 0;
		line++;
	}
	if (in_dquote)
		return (eof_err("\""), 0);
	if (in_quote)
		return (eof_err("'"), 0);
	return (1);
}

bool	is_syntax_correct(char *line)
{
	if (!check_quotes(line))
		return (0);
	return (1);
}
