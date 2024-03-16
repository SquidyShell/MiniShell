/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:46:32 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/16 11:37:37 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_vars(t_vars *v)
{
	v->pipe_nb = 0;
	v->index = 0;
	v->in_quote = 0;
	v->in_dquote = 0;
	v->in_expanded_var = 0;
	v->end_of_var = 0;
	v->command_was_built_in = 0;
	v->tokens = NULL;
	v->cmd.args = NULL;
}

int	parse_the_actual_char(t_vars *v)
{
	if (needs_to_be_expanded(v))
	{
		if (expand_this_shit(v) == -1)
			return (-1);
	}
	else
	{
		if (v->line[v->index] == '\"')
		{
			if (there_is_a_dquote(v) == -1)
				return (-1);
		}
		if (v->line[v->index] == '\'')
		{
			if (there_is_a_quote(v) == -1)
				return (-1);
		}
		if (!v->in_quote && !v->in_dquote)
		{
			if (not_in_quote(v) == -1)
				return (-1);
		}
	}
	return (0);
}

int	parsing(t_vars *v)
{
	v->line_was_expanded = 0;
	if (!is_syntax_correct(v->line, v))
		return (-1);
	while (v->line[v->index])
	{
		if (v->in_expanded_var && v->index > v->end_of_var)
			v->in_expanded_var = 0;
		if (parse_the_actual_char(v) == -1)
			return (-1);
		v->index++;
	}
	if (tok_close(v) == -1)
		return (-1);
	if (v->tokens && is_metachar(*v->tokens->last))
		return (berr("newline", v), -1);
	tok_print(v->tokens);
	return (0);
}
