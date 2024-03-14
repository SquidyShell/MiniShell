/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:29:44 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/14 02:01:32 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char **cmd, t_vars *vars)
{
	printfd(STDIN, "exit\n");
	if (cmd[2])
		return (printfd(STDERR, "🦑: exit: too many arguments\n"));
	if (cmd[1])
		exit(ft_atoi(cmd[1]) % 256);
	else
		exit(vars->exit_status);
	(void)vars;
	(void)cmd;
}
