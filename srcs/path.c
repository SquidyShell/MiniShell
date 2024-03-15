/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 17:59:30 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/15 21:20:44 by legrandc         ###   ########.fr       */
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
