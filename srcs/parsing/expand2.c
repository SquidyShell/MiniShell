/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 06:09:09 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/11 22:52:12 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	needs_to_be_expanded(t_vars *v)
{
	if (v->tokens)
		return (v->line[v->index] == '$' && !v->in_quote
			&& v->tokens->last->type != DLESS && v->line[v->index + 1]
			&& !is_whitespace(v->line[v->index + 1]));
	else
		return (v->line[v->index] == '$' && v->line[v->index + 1]
			&& !v->in_quote && !is_whitespace(v->line[v->index + 1]));
}
