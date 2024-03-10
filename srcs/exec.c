/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:41:04 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/10 18:52:08 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_fds(t_vars *vars)
{
	close(vars->fildes[0]);
	close(vars->fildes[1]);
}

void	search_and_execve(t_vars *vars)
{
	char	**args;

	args = vars->cmd.args;
	if (!args || get_path(args[0], vars) == -1)
		exit(EXIT_FAILURE);
	if (vars->cmd.path == NULL)
	{
		if (args[0])
			ft_putstr_fd(args[0], STDERR_FILENO);
		ft_printfd(STDERR_FILENO, ": command not found\n");
	}
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
	close(vars->fildes[0]);
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
	while (curr)
	{
		get_cmd_infos(&curr, vars);
		is_builtin(vars);
		free(vars->cmd.args);
	}
	return (wait_commands(vars));
}
