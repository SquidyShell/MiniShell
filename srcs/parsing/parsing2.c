/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 06:09:09 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/11 13:01:35 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	case_pipe(t_vars *vars)
{
	bool	last_meta;

	last_meta = false;
	if (vars->tokens && vars->last_token->type == PIPE
		&& vars->last_token->closed == false)
		vars->last_token->type = OR_IF;
	else
	{
		if (!vars->tokens || is_metachar(*vars->last_token))
			last_meta = true;
		if (tok_close(vars) == -1)
			return (-1);
		tok_addback(vars, tok_new(NULL, PIPE));
		vars->last_token->error = last_meta;
	}
	return (0);
}

int	case_less(t_vars *vars)
{
	bool	last_meta;

	last_meta = false;
	if (vars->tokens && vars->last_token->type == LESS
		&& vars->last_token->closed == false)
		vars->last_token->type = DLESS;
	else
	{
		if (vars->tokens && is_metachar(*vars->last_token))
			last_meta = true;
		if (tok_close(vars) == -1)
			return (-1);
		tok_addback(vars, tok_new(NULL, LESS));
		vars->last_token->error = last_meta;
	}
	return (0);
}

int	case_great(t_vars *vars)
{
	bool	last_meta;

	last_meta = false;
	if (vars->tokens && vars->last_token->type == GREAT
		&& vars->last_token->closed == false)
		vars->last_token->type = DGREAT;
	else
	{
		if (vars->tokens && is_metachar(*vars->last_token))
			last_meta = true;
		if (tok_close(vars) == -1)
			return (-1);
		tok_addback(vars, tok_new(NULL, GREAT));
		vars->last_token->error = last_meta;
	}
	return (0);
}

int	case_word(t_vars *vars)
{
	if (vars->tokens && (vars->last_token->type == LESS
			|| vars->last_token->type == DLESS))
	{
		if (tok_close(vars) == -1)
			return (-1);
		tok_addback(vars, tok_new(NULL, FILE_IN));
	}
	else if (vars->tokens && (vars->last_token->type == GREAT
			|| vars->last_token->type == DGREAT))
	{
		if (tok_close(vars) == -1)
			return (-1);
		tok_addback(vars, tok_new(NULL, FILE_OUT));
	}
	else if (vars->tokens && (is_metachar(*vars->last_token)))
		if (tok_close(vars) == -1)
			return (-1);
	if (!vars->tokens || vars->last_token->closed == true)
		tok_addback(vars, tok_new(NULL, WORD));
	return (0);
}
