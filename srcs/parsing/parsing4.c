/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:46:32 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/12 13:38:03 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	not_in_quote(t_vars *v)
{
	if (is_whitespace(v->line[v->index]))
	{
		if (tok_close(v) == -1)
			return (-1);
	}
	else if (get_type_and_len(v) == -1)
		return (-1);
	return (1);
}

int	there_is_a_quote(t_vars *v)
{
	if (!v->in_dquote)
	{
		if (!v->in_quote)
		{
			v->in_quote = 1;
			if (v->tokens)
				v->tokens->last->is_single_quoted = 1;
			if (case_word(v) == -1)
				return (-1);
		}
		else
			v->in_quote = 0;
	}
	return (1);
}

int	there_is_a_dquote(t_vars *v)
{
	if (!v->in_quote)
	{
		if (!v->in_dquote)
		{
			v->in_dquote = 1;
			if (v->tokens)
				v->tokens->last->is_double_quoted = 1;
			if (case_word(v) == -1)
				return (-1);
		}
		else
			v->in_dquote = 0;
	}
	return (1);
}
