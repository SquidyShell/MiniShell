/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 07:44:16 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/13 13:02:27 by cviegas          ###   ########.fr       */
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
	else
		return (0);
	return (1);
}
