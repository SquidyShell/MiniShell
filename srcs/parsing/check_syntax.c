/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:29:12 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/10 18:44:11 by cviegas          ###   ########.fr       */
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
		if (!in_quote && !in_dquote)
			if (*line == '\'')
				in_quote = 1;
	}
}

bool	is_syntax_correct(char *line)
{
	if (!check_quotes(line))
		return (0);
	return (1);
}
