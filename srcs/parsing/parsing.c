/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:46:32 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/11 17:29:49 by cviegas          ###   ########.fr       */
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

int	search_for_lenght(t_vars *vars)
{
	if (vars->line[vars->index] == '|')
		return (case_pipe(vars));
	else if (vars->line[vars->index] == '<')
		return (case_less(vars));
	else if (vars->line[vars->index] == '>')
		return (case_great(vars));
	else
		return (case_word(vars));
}

int	get_type_and_len(t_vars *vars)
{
	return (search_for_lenght(vars));
}

int	parsing(t_vars *v)
{
	if (!is_syntax_correct(v->line))
		return (-1);
	v->in_quote = 0;
	v->in_dquote = 0;
	while (v->line[v->index])
	{
		if (v->line[v->index] && !v->in_quote)
		{
			if (is_whitespace(v->line[v->index]))
			{
				if (tok_close(v) == -1)
					return (-1);
			}
			else if (v->line[v->index] == '\'')
				if_quote(v);
			else if (get_type_and_len(v) == -1)
				return (-1);
		}
		v->index++;
	}
	if (tok_close(v) == -1)
		return (-1);
	if (v->tokens && is_metachar(*v->last_token))
		return (berr("newline"), -1);
	tok_print(v->tokens);
	return (0);
}
