/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:41:04 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/16 14:57:02 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_child(t_vars *vars)
{
	get_fds(vars);
	if (redirect(vars) == -1)
		exit(EXIT_FAILURE);
	if (is_builtin(vars))
		vars->function(vars->cmd.args, vars);
	else
		search_and_execve(vars);
	clean_vars(vars);
	exit(EXIT_SUCCESS);
}

static int	pipex(t_vars *vars)
{
	if (vars->cmd_i != vars->pipe_nb)
	{
		if (pipe(vars->fildes) == -1)
			return (-1);
	}
	vars->last_pid = fork();
	if ((vars->last_pid) == -1)
		return (-1);
	if ((vars->last_pid) == 0)
		exec_child(vars);
	if (vars->cmd_i)
		close(vars->last_fd);
	vars->last_fd = vars->fildes[0];
	if (vars->cmd_i != vars->pipe_nb)
		close(vars->fildes[1]);
	return (0);
}

void	case_no_pipe(t_vars *vars)
{
	if (vars->cmd.args[0] && vars->cmd.len && is_builtin(vars))
	{
		vars->old_stdout = dup(STDOUT_FILENO);
		if (redirect(vars) == -1)
			return ;
		vars->function(vars->cmd.args, vars);
		dup2_and_close(vars->old_stdout, STDOUT_FILENO);
	}
	else
		pipex(vars);
}

int	exec_list(t_tokens **curr, t_vars *vars)
{
	bool	is_ignored;

	vars->cmd_i = 0;
	vars->last_pid = 0;
	while ((*curr) && (*curr)->type != OR_IF && (*curr)->type != AND_IF)
	{
		is_ignored = vars->ignore_lvl != 0;
		set_signals_child(vars);
		vars->infile_fd = -1;
		vars->outfile_fd = -1;
		vars->cmd.token = (*curr);
		if (get_cmd_infos(curr, vars) == -1)
			return (-1);
		if (!is_ignored)
		{
			if (vars->cmd.len && vars->pipe_nb)
				pipex(vars);
			else
				case_no_pipe(vars);
			p_free(vars->cmd.args);
			vars->cmd_i++;
		}
	}
	return (wait_commands(vars));
}

int	exec(t_vars *vars)
{
	t_tokens	*curr;

	curr = vars->tokens;
	vars->last_pid = 0;
	vars->ignore_lvl = 0;
	while (curr)
	{
		exec_list(&curr, vars);
		if (vars->ignore_lvl > 0)
			vars->ignore_lvl--;
		if (curr && curr->type == OR_IF)
		{
			if (g_exit_status == 0 && !vars->ignore_lvl)
				vars->ignore_lvl = 1;
		}
		else if (curr && curr->type == AND_IF)
		{
			if (g_exit_status != 0 && !vars->ignore_lvl)
				vars->ignore_lvl = 1;
		}
		else
			continue ;
		curr = curr->next;
	}
	return (g_exit_status);
}
