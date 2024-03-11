/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:41:04 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/11 22:39:24 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_fds(t_vars *vars)
{
	if (vars->cmd_i)
	{
		dup2(vars->last_fd, STDIN_FILENO);
		close(vars->last_fd);
	}
	if (vars->cmd_i != vars->pipe_nb)
	{
		dup2(vars->fildes[1], STDOUT_FILENO);
		close(vars->fildes[0]);
		close(vars->fildes[1]);
	}
}

void	search_and_execve(t_vars *vars)
{
	char	**args;

	args = vars->cmd.args;
	if (!args || get_path(args[0], vars) == -1)
		exit(EXIT_FAILURE);
	if (vars->cmd.path == NULL)
		printfd(STDERR_FILENO, "%s: command not found\n", args[0]);
	else if (access(vars->cmd.path, F_OK) == -1 && errno == ENOENT)
		perror(vars->cmd.path);
	else
	{
		execve(vars->cmd.path, args, vars->env);
		perror(vars->cmd.path);
		g_exit_status = 126;
	}
	free(vars->cmd.path);
	free_matrix(vars->env_path);
	tok_clear(&vars->tokens);
	free(args);
	exit(g_exit_status);
}

static int	pipex(t_vars *vars)
{
	if (vars->cmd_i != vars->pipe_nb)
		if (pipe(vars->fildes) == -1)
			return (-1);
	vars->last_pid = fork();
	if ((vars->last_pid) == -1)
		return (-1);
	if ((vars->last_pid) == 0)
	{
		get_fds(vars);
		if (!vars->cmd.builtin)
			search_and_execve(vars);
	}
	if (vars->cmd_i)
		close(vars->last_fd);
	vars->last_fd = vars->fildes[0];
	if (vars->cmd_i != vars->pipe_nb)
		close(vars->fildes[1]);
	return (0);
}

int	is_builtin(t_vars *vars)
{
	if (!ft_strcmp(vars->cmd.args[0], "echo"))
		ft_echo(vars->cmd.args, vars);
	else if (!ft_strcmp(vars->cmd.args[0], "cd"))
		ft_cd(vars->cmd.args, vars);
	else if (!ft_strcmp(vars->cmd.args[0], "pwd"))
		ft_pwd(vars->cmd.args, vars);
	else if (!ft_strcmp(vars->cmd.args[0], "export"))
		ft_export(vars->cmd.args, vars);
	else if (!ft_strcmp(vars->cmd.args[0], "unset"))
		ft_unset(vars->cmd.args, vars);
	else if (!ft_strcmp(vars->cmd.args[0], "env"))
		ft_env(vars->cmd.args, vars);
	else if (!ft_strcmp(vars->cmd.args[0], "exit"))
		ft_exit(vars->cmd.args, vars);
	else
		return (pipex(vars), 0);
	return (1);
}

int	exec(t_vars *vars)
{
	t_tokens	*curr;

	curr = vars->tokens;
	vars->last_pid = 0;
	while (curr)
	{
		vars->cmd.files = NULL;
		perr("tokens:");
		tok_print(curr);
		get_cmd_infos(&curr, vars);
		perr("files:");
		tok_print(vars->cmd.files);
		if (vars->cmd.len)
			is_builtin(vars);
		free(vars->cmd.args);
		vars->cmd_i++;
	}
	return (wait_commands(vars));
}
