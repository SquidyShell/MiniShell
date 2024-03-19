/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 17:58:12 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/19 23:20:29 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_commands(t_vars *vars)
{
	int	code;
	int	pid;
	int	wstatus;

	while (1)
	{
		pid = wait(&wstatus);
		if (pid == -1)
			break ;
		if (WIFEXITED(wstatus))
			code = WEXITSTATUS(wstatus);
		else
		{
			code = 128 + WTERMSIG(wstatus);
			if (code == 130)
				printfd(2, "\n");
			if (code == 131)
				printfd(2, "Quit (core dumped)\n");
		}
		if (pid == vars->last_pid)
			g_exit_status = code;
	}
	return (g_exit_status);
}
