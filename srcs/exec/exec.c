/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:41:04 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/13 19:24:02 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_child(t_vars *vars)
{
	set_signals_child(vars);
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
	if (vars->cmd.len && is_builtin(vars))
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

int	exec(t_vars *vars)
{
	t_tokens	*curr;

	curr = vars->tokens;
	vars->last_pid = 0;
	while (curr)
	{
		vars->infile_fd = -1;
		vars->outfile_fd = -1;
		vars->cmd.token = curr;
		if (get_cmd_infos(&curr, vars) == -1)
			return (-1);
		if (vars->cmd.len && vars->pipe_nb)
			pipex(vars);
		else
			case_no_pipe(vars);
		free(vars->cmd.args);
		vars->cmd_i++;
	}
	return (wait_commands(vars));
}
