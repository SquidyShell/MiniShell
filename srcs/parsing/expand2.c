/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 06:09:09 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/15 20:10:00 by cviegas          ###   ########.fr       */
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

int	var_is_exit_status(t_vars *v)
{
	char	*var_value;

	var_value = ft_itoa(v->exit_status);
	if (!var_value)
		return (perr("Malloc"), -1);
	if (replace_var_name_by_value(v, var_value, 1) == -1)
		return (free(var_value), perr("Malloc"), -1);
	free(var_value);
	return (1);
}
