/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:29:12 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/16 03:28:39 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	parse_actual_char(char *line, bool *in_s_and_d_quote[],
		size_t *par_in_and_out[])
{
	if (!*in_s_and_d_quote[0] && !*in_s_and_d_quote[1] && *line == '\'')
		*in_s_and_d_quote[0] = 1;
	else if (*in_s_and_d_quote[0] && *line == '\'')
		*in_s_and_d_quote[0] = 0;
	if (!*in_s_and_d_quote[0] && !*in_s_and_d_quote[1] && *line == '\"')
		*in_s_and_d_quote[1] = 1;
	else if (*in_s_and_d_quote[1] && *line == '\"')
		*in_s_and_d_quote[1] = 0;
	if (!*in_s_and_d_quote[1] && !*in_s_and_d_quote[0])
	{
		if (*line == '(')
			++*par_in_and_out[0];
		else if (*line == ')')
			++*par_in_and_out[1];
	}
}

bool	is_syntax_correct(char *line, t_vars *v)
{
	bool	in_dquote;
	bool	in_quote;
	size_t	par_in;
	size_t	par_out;

	par_in = 0;
	par_out = 0;
	in_dquote = 0;
	in_quote = 0;
	while (*line)
	{
		parse_actual_char(line, (bool *[]){&in_quote, &in_dquote},
			(size_t *[]){&par_in, &par_out});
		if (par_in < par_out)
			return (berr(")", v), 0);
		line++;
	}
	if (par_in > par_out)
		return (eof_err(")", v), 0);
	if (in_dquote)
		return (eof_err("\"", v), 0);
	if (in_quote)
		return (eof_err("'", v), 0);
	return (1);
}

// bool	is_syntax_correct(char *line, t_vars *v)
// {
// 	bool	in_dquote;
// 	bool	in_quote;
// 	size_t	par_in;
// 	size_t	par_out;

// 	par_in = 0;
// 	par_out = 0;
// 	in_dquote = 0;
// 	in_quote = 0;
// 	while (*line)
// 	{
// 		if (!in_quote && !in_dquote && *line == '\'')
// 			in_quote = 1;
// 		else if (in_quote && *line == '\'')
// 			in_quote = 0;
// 		if (!in_quote && !in_dquote && *line == '\"')
// 			in_dquote = 1;
// 		else if (in_dquote && *line == '\"')
// 			in_dquote = 0;
// 		if (!in_dquote && !in_quote)
// 		{
// 			if (*line == '(')
// 				par_in++;
// 			else if (*line == ')')
// 				par_out++;
// 		}
// 		if (par_in < par_out)
// 			return (berr(")", v), 0);
// 		line++;
// 	}
// 	if (par_in > par_out)
// 		return (eof_err(")", v), 0);
// 	if (in_dquote)
// 		return (eof_err("\"", v), 0);
// 	if (in_quote)
// 		return (eof_err("'", v), 0);
// 	return (1);
// }