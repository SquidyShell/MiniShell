/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:46:32 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/11 21:26:42 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_vars(t_vars *v)
{
	v->pipe_nb = 0;
	v->cmd_i = 0;
	v->index = 0;
	v->in_quote = 0;
	v->in_dquote = 0;
	v->tokens = NULL;
}

int	parsing(t_vars *v)
{
	if (!is_syntax_correct(v->line))
		return (-1);
	while (v->line[v->index])
	{
		if (v->line[v->index])
		{
			if (needs_to_be_expanded(v))
				expand_this_shit(v);
			if (v->line[v->index] == '\"')
				there_is_a_dquote(v);
			if (v->line[v->index] == '\'')
				there_is_a_quote(v);
			if (!v->in_quote)
				not_in_quote(v);
		}
		v->index++;
	}
	if (tok_close(v) == -1)
		return (-1);
	if (v->tokens && is_metachar(*v->tokens->last))
		return (berr("newline"), -1);
	tok_print(v->tokens);
	return (0);
}
