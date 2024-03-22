/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 07:44:16 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/22 13:13:39 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_vars *vars)
{
	if (!ft_strcmp(vars->cmd.args[0], "echo"))
		vars->function = ft_echo;
	else if (!ft_strcmp(vars->cmd.args[0], "cd"))
		vars->function = ft_cd;
	else if (!ft_strcmp(vars->cmd.args[0], "pwd"))
		vars->function = ft_pwd;
	else if (!ft_strcmp(vars->cmd.args[0], "export"))
		vars->function = ft_export;
	else if (!ft_strcmp(vars->cmd.args[0], "unset"))
		vars->function = ft_unset;
	else if (!ft_strcmp(vars->cmd.args[0], "env"))
		vars->function = ft_env;
	else if (!ft_strcmp(vars->cmd.args[0], "exit"))
		vars->function = ft_exit;
	else if (!ft_strcmp(vars->cmd.args[0], "gigit"))
		vars->function = gigit;
	else
		return (0);
	if (vars->function != ft_exit)
		g_exit_status = 0;
	vars->command_was_built_in = 1;
	return (1);
}

char	*ft_getcwd(void)
{
	char	*ret;
	char	*buff;
	size_t	size;

	ret = NULL;
	buff = NULL;
	size = 100;
	while (1)
	{
		ret = getcwd(buff, size);
		free(buff);
		size *= 2;
		if (errno == ERANGE)
			continue ;
		else
			break ;
	}
	return (ret);
}
