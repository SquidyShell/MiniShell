/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 22:48:09 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/20 18:44:27 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	change_ignore_lvl(size_t *ignore_lvl, size_t type)
{
	if (*ignore_lvl)
	{
		if (type == PARENTHESES_IN)
			(*ignore_lvl)++;
		else if (type == PARENTHESES_OUT)
			(*ignore_lvl)--;
	}
}

void	p_free(void *p)
{
	if (p)
	{
		free(p);
		p = NULL;
	}
}

void	clean_vars(t_vars *vars)
{
	ft_close(&vars->old_stdin);
	p_free(vars->readlinestring);
	ft_lstclear(&vars->env_list, free);
	ft_lstclear(&vars->history, free);
	p_free(vars->cmd.path);
	if (vars->tokens)
		tok_clear(&vars->tokens);
	free_matrix(vars->env_path);
	p_free(vars->env);
	p_free(vars->cmd.args);
	ft_close(&vars->fildes[0]);
	ft_close(&vars->fildes[1]);
}
