/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:29:44 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/15 11:01:41 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char **cmd, t_vars *vars)
{
	printfd(STDIN, "exit\n");
	if (cmd[2])
	{
		printf("%p %s", cmd[2], cmd[2]);
		return (printfd(STDERR, "🦑: exit: too many arguments\n"));
	}
	if (cmd[1])
		exit(ft_atoi(cmd[1]) % 256);
	else
		exit(vars->exit_status);
	(void)vars;
	(void)cmd;
}
