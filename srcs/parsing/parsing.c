/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:46:32 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/21 18:39:52 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

int	parse_tokens(t_tokens *tok)
{
	t_tokens	*curr;

	if (!(tok))
		return (0);
	curr = tok;
	while (curr)
	{
		if (needs_to_remove_quotes(curr) && maybe_remove_quotes(curr) == -1)
			return (-1);
		if (is_expandable(curr) && maybe_expand(curr) == -1)
			return (-1);
		curr = curr->next;
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
		if (parse_the_actual_char(v) == -1)
			return (-1);
		v->index++;
	}
	if (tok_close(v) == -1)
		return (-1);
	if (v->tokens && is_metachar(*v->tokens->last))
		return (berr("newline", v), -1);
	if (parse_tokens(v->tokens) == -1)
		return (-1);
	return (0);
}

// if (parse_token_list(&v->tokens) == -1)
// 	return (-1);
