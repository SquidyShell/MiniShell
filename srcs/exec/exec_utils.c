/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 22:48:09 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/22 11:59:58 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	update_dash(t_vars *v)
{
	ft_unset((char *[]){"unset", "_", NULL}, v);
	v->tmp = ft_strjoin("_=", v->cmd.args[v->cmd.len - 1]);
	(ft_export((char *[]){"export", v->tmp, NULL}, v), free(v->tmp));
}

void	init_cmd(t_vars *v)
{
	v->pipe_nb = 0;
	v->cmd_i = 0;
	v->last_pid = 0;
}

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
	vars->readlinestring = NULL;
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
