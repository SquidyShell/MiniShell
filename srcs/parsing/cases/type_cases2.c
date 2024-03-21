/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_cases2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 08:23:53 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/21 04:18:55 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_cmd_len(t_vars *vars, t_tokens *tokens, size_t ignore_lvl)
{
	bool	is_skipped;

	is_skipped = ignore_lvl != 0;
	vars->cmd.len = 0;
	while (tokens && tokens->type != PIPE && should_continue(tokens->type,
			ignore_lvl))
	{
		change_ignore_lvl(&ignore_lvl, tokens->type);
		if (tokens->type == WORD)
			vars->cmd.len++;
		tokens = tokens->next;
	}
	if (!is_skipped && vars->cmd.len)
	{
		vars->cmd.args = malloc(sizeof(*vars->cmd.args) * (vars->cmd.len + 1));
		if (!vars->cmd.args)
			(clean_vars(vars), err_squid("Malloc error during parsing", 0),
				exit(EXIT_FAILURE));
		vars->cmd.args[vars->cmd.len] = 0;
	}
	return (0);
}

int	get_cmd_infos(t_tokens **curr, t_vars *vars)
{
	size_t	i;
	bool	is_skipped;

	is_skipped = vars->ignore_lvl != 0;
	if (get_cmd_len(vars, (*curr), vars->ignore_lvl) == -1)
		return (-1);
	i = 0;
	while ((*curr) && (*curr)->type != PIPE && should_continue((*curr)->type,
			vars->ignore_lvl))
	{
		change_ignore_lvl(&vars->ignore_lvl, (*curr)->type);
		if ((*curr)->type == WORD && !is_skipped)
			vars->cmd.args[i] = (*curr)->content;
		if ((*curr)->type == WORD)
			i++;
		(*curr) = (*curr)->next;
	}
	if ((*curr) && (*curr)->type == PIPE)
	{
		vars->pipe_nb++;
		(*curr) = (*curr)->next;
	}
	vars->cmd.builtin = 0;
	return (0);
}

bool	is_there_operation_err(t_vars *vars)
{
	return (vars->tokens && vars->tokens->last
		&& vars->tokens->last->type == PARENTHESES_OUT
		&& (!(vars->line[vars->index] == '&' && vars->line[vars->index
					+ 1] == '&') && !(vars->line[vars->index] == '|'
				|| vars->line[vars->index + 1] == '|')));
}

int	what_token_type_is_it(t_vars *vars)
{
	if (vars->line[vars->index] == '(')
		return (case_parenthese(vars, PARENTHESES_IN));
	if (vars->line[vars->index] == ')')
		return (case_parenthese(vars, PARENTHESES_OUT));
	if (is_there_operation_err(vars))
		return (berr(")", vars), -1);
	if (vars->line[vars->index] == '&' && vars->line[vars->index + 1] == '&')
		return (case_and(vars));
	if (vars->line[vars->index] == '|')
		return (case_pipe(vars));
	if (vars->line[vars->index] == '<')
		return (case_less(vars));
	if (vars->line[vars->index] == '>')
		return (case_great(vars));
	return (case_word(vars));
}

int	case_parenthese(t_vars *vars, int type)
{
	if (type == PARENTHESES_OUT && vars->tokens)
	{
		if (vars->tokens->last->type == PARENTHESES_IN)
			return (berr(")", vars), -1);
	}
	if (type == PARENTHESES_IN && vars->tokens)
	{
		if (vars->tokens->type != AND_IF && vars->tokens->type != OR_IF)
		{
			if (vars->tokens->last && (vars->tokens->last->type != AND_IF
					&& vars->tokens->last->type != OR_IF))
				return (berr("(", vars), -1);
		}
	}
	if (!tok_close_and_addback(&vars->tokens, vars, type))
		return (-1);
	if (vars->tokens)
		vars->tokens->last->type = type;
	return (0);
}
