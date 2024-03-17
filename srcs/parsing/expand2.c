/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 06:09:09 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/17 04:11:17 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_snakecase(char c)
{
	return (ft_isalnum(c) || (c == '_'));
}

bool	is_snakecase_or_qmark(char c)
{
	return (is_snakecase(c) || (c == '?'));
}

bool	needs_to_be_expanded(t_vars *v)
{
	if (v->in_expanded_var && v->index >= v->end_of_var)
	{
		v->in_expanded_var = 0;
		v->end_of_var = 0;
	}
	if (v->tokens)
		return (v->line[v->index] == '$' && !v->in_quote
			&& v->tokens->last->type != DLESS && v->line[v->index + 1]
			&& !is_whitespace(v->line[v->index + 1])
			&& is_snakecase_or_qmark(v->line[v->index + 1]));
	else
		return (v->line[v->index] == '$' && v->line[v->index + 1]
			&& !v->in_quote && !is_whitespace(v->line[v->index + 1])
			&& is_snakecase_or_qmark(v->line[v->index + 1]));
}

int	var_is_exit_status(t_vars *v)
{
	char	*var_value;

	var_value = ft_itoa(g_exit_status);
	if (!var_value)
		return (err_squid("Malloc", true), -1);
	if (replace_var_name_by_value(v, var_value, 1) == -1)
		return (free(var_value), err_squid("Malloc", true), -1);
	free(var_value);
	return (1);
}
