/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 17:59:30 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/19 12:02:05 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_path(char *command, t_vars *vars)
{
	char	*tested_path;
	size_t	i;

	if (!command || !ft_strcmp(command, ".") || !command[0])
		return (0);
	if (ft_strchr(command, '/'))
		return (vars->cmd.path = ft_strdup(command), (vars->cmd.path != NULL)
			- 1);
	i = 0;
	while (vars->env_path && vars->env_path[i])
	{
		tested_path = ft_strjoin3(vars->env_path[i], "/", command);
		if (!tested_path)
			return (-1);
		if (access(tested_path, F_OK) == 0)
			return (vars->cmd.path = tested_path, 0);
		free(tested_path);
		i++;
	}
	g_exit_status = 127;
	return (0);
}

void	search_and_execve(t_vars *vars)
{
	char	**args;

	args = vars->cmd.args;
	if (!args || get_path(args[0], vars) == -1)
		(clean_vars(vars), exit(EXIT_FAILURE));
	if (vars->cmd.path == NULL)
		printfd(STDERR, SQUID "%s: command not found\n", args[0]);
	else if (access(vars->cmd.path, F_OK) == -1 && errno == ENOENT)
		err_squid(vars->cmd.path, true);
	else
	{
		if (turn_env_into_char(vars) == -1)
			s();
		s();
		execve(vars->cmd.path, args, vars->env);
		err_squid(vars->cmd.path, true);
		g_exit_status = 126;
	}
	clean_vars(vars);
	exit(g_exit_status);
}
