/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:41:04 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/22 12:27:45 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_child(t_vars *vars)
{
	signal(SIGQUIT, SIG_DFL);
	vars->is_child = true;
	get_fds(vars);
	if (redirect(vars) == -1)
	{
		clean_vars(vars);
		exit(EXIT_FAILURE);
	}
	if (vars->cmd.len && is_builtin(vars))
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
		ft_close(&vars->last_fd);
	vars->last_fd = vars->fildes[0];
	if (vars->cmd_i != vars->pipe_nb)
		ft_close(&vars->fildes[1]);
	return (0);
}

void	case_no_pipe(t_vars *vars)
{
	if (vars->cmd.len && vars->cmd.args[0] && is_builtin(vars))
	{
		vars->old_stdin = dup(STDIN_FILENO);
		if (vars->old_stdin == -1)
			(clean_vars(vars), err_squid("dup()", 1), exit(EXIT_FAILURE));
		vars->old_stdout = dup(STDOUT_FILENO);
		if (vars->old_stdout == -1)
			(clean_vars(vars), err_squid("dup()", 1), exit(EXIT_FAILURE));
		if (redirect(vars) == -1)
			g_exit_status = 1;
		else
			vars->function(vars->cmd.args, vars);
		dup2_and_close(&vars->old_stdin, STDIN_FILENO);
		dup2_and_close(&vars->old_stdout, STDOUT_FILENO);
	}
	else
		pipex(vars);
}

static void	exec_list(t_tokens **curr, t_vars *v)
{
	bool	is_ignored;

	init_cmd(v);
	while ((*curr) && (*curr)->type != OR_IF && (*curr)->type != AND_IF)
	{
		is_ignored = v->ignore_lvl != 0;
		v->infile_fd = -2;
		v->outfile_fd = -2;
		v->cmd.token = (*curr);
		get_cmd_infos(curr, v);
		if (!is_ignored)
		{
			if (v->cmd.len)
				update_dash(v);
			if (v->pipe_nb)
				pipex(v);
			else
				case_no_pipe(v);
			(p_free(v->cmd.args), v->cmd.args = NULL);
			v->cmd_i++;
		}
	}
	g_exit_status = wait_commands(v);
}

int	exec(t_vars *vars)
{
	t_tokens	*curr;

	if (vars->line_was_expanded)
		free(vars->line);
	if (!vars->tokens && vars->line_was_expanded)
		g_exit_status = 0;
	curr = vars->tokens;
	vars->last_pid = 0;
	vars->ignore_lvl = 0;
	while (curr)
	{
		exec_list(&curr, vars);
		if (vars->ignore_lvl > 0)
			vars->ignore_lvl--;
		if ((curr && curr->type == OR_IF) || (curr && curr->type == AND_IF))
		{
			if ((curr->type == OR_IF && g_exit_status == 0 && !vars->ignore_lvl
					&& curr->type == OR_IF) || (curr->type == AND_IF
					&& g_exit_status != 0 && !vars->ignore_lvl))
				vars->ignore_lvl = 1;
			curr = curr->next;
		}
	}
	return (g_exit_status);
}
