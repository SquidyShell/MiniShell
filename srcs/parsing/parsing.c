/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:46:32 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/11 09:28:00 by legrandc         ###   ########.fr       */
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

int	parsing(t_vars *vars)
{
	while (vars->line[vars->index])
	{
		if (is_whitespace(vars->line[vars->index]))
		{
			if (tok_close(vars) == -1)
				return (-1);
		}
		else if (get_type_and_len(vars) == -1)
			return (-1);
		vars->index++;
	}
	if (tok_close(vars) == -1)
		return (-1);
	if (vars->tokens && is_metachar(*vars->last_token))
		return (berr("newline"), -1);
	tok_print(vars->tokens);
	return (0);
}
