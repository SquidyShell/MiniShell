/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 06:09:09 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/11 18:15:07 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	case_pipe(t_vars *vars)
{
	bool	last_meta;

	last_meta = false;
	if (vars->tokens && vars->tokens->last->type == PIPE
		&& vars->tokens->last->closed == false)
		vars->tokens->last->type = OR_IF;
	else
	{
		if (!vars->tokens || is_metachar(*vars->tokens->last))
			last_meta = true;
		if (tok_close(vars) == -1)
			return (-1);
		tok_addback(vars, tok_new(NULL, PIPE));
		vars->tokens->last->error = last_meta;
	}
	return (0);
}

int	case_less(t_vars *vars)
{
	bool	last_meta;

	last_meta = false;
	if (vars->tokens && vars->tokens->last->type == LESS
		&& vars->tokens->last->closed == false)
		vars->tokens->last->type = DLESS;
	else
	{
		if (vars->tokens && is_metachar(*vars->tokens->last))
			last_meta = true;
		if (tok_close(vars) == -1)
			return (-1);
		tok_addback(vars, tok_new(NULL, LESS));
		vars->tokens->last->error = last_meta;
	}
	return (0);
}

int	case_great(t_vars *vars)
{
	bool	last_meta;

	last_meta = false;
	if (vars->tokens && vars->tokens->last->type == GREAT
		&& vars->tokens->last->closed == false)
		vars->tokens->last->type = DGREAT;
	else
	{
		if (vars->tokens && is_metachar(*vars->tokens->last))
			last_meta = true;
		if (tok_close(vars) == -1)
			return (-1);
		tok_addback(vars, tok_new(NULL, GREAT));
		vars->tokens->last->error = last_meta;
	}
	return (0);
}

int	case_word(t_vars *vars)
{
	if (vars->tokens && (vars->tokens->last->type == LESS
			|| vars->tokens->last->type == DLESS))
	{
		if (tok_close(vars) == -1)
			return (-1);
		tok_addback(vars, tok_new_quoted(NULL, FILE_IN, vars->in_quote,
				vars->in_dquote));
	}
	else if (vars->tokens && (vars->tokens->last->type == GREAT
			|| vars->tokens->last->type == DGREAT))
	{
		if (tok_close(vars) == -1)
			return (-1);
		tok_addback(vars, tok_new_quoted(NULL, FILE_OUT, vars->in_quote,
				vars->in_dquote));
	}
	else if (vars->tokens && (is_metachar(*vars->tokens->last)))
		if (tok_close(vars) == -1)
			return (-1);
	if (!vars->tokens || vars->tokens->last->closed == true)
		tok_addback(vars, tok_new_quoted(NULL, WORD, vars->in_quote,
				vars->in_dquote));
	return (0);
}
