/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 08:23:53 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/11 12:39:09 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_cmd_len(t_vars *vars, t_tokens *tokens)
{
	vars->cmd.len = 0;
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == WORD)
			vars->cmd.len++;
		tokens = tokens->next;
	}
	return (0);
}

int	get_cmd_infos(t_tokens **curr, t_vars *vars)
{
	size_t	i;

	if (get_cmd_len(vars, (*curr)) == -1)
		return (-1);
	vars->cmd.args = malloc(sizeof(*vars->cmd.args) * (vars->cmd.len + 1));
	if (!vars->cmd.args)
		return (-1);
	vars->cmd.args[vars->cmd.len] = 0;
	i = 0;
	while ((*curr) && (*curr)->type != PIPE)
	{
		if ((*curr)->type == WORD)
			vars->cmd.args[i++] = (*curr)->content;
		(*curr) = (*curr)->next;
	}
	if ((*curr) && (*curr)->type == PIPE)
		(*curr) = (*curr)->next;
	vars->cmd.builtin = 0;
	return (0);
}
