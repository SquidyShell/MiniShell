/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 06:09:09 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/12 14:09:37 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	needs_to_be_expanded(t_vars *v)
{
	if (v->in_expanded_var && v->index > v->end_of_var)
	{
		v->in_expanded_var = 0;
		v->end_of_var = 0;
	}
	if (v->tokens)
		return (v->line[v->index] == '$' && !v->in_quote
			&& v->tokens->last->type != DLESS && v->line[v->index + 1]
			&& !is_whitespace(v->line[v->index + 1]));
	else
		return (v->line[v->index] == '$' && v->line[v->index + 1]
			&& !v->in_quote && !is_whitespace(v->line[v->index + 1]));
}
