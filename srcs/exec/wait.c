/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 17:58:12 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/13 21:34:13 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_commands(t_vars *vars)
{
	int	ret;
	int	wstatus;

	while (errno != ECHILD)
	{
		if (wait(&wstatus) == vars->last_pid)
		{
			if (WIFEXITED(wstatus))
				ret = WEXITSTATUS(wstatus);
			else
				ret = 128 + WTERMSIG(wstatus);
		}
	}
	if (vars->command_was_built_in)
		return (vars->exit_status);
	else
		return (ret);
}
