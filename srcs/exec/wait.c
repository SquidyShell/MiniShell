/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 17:58:12 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/15 21:16:39 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_commands(t_vars *vars)
{
	int	ret;
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
			code = 128 + WTERMSIG(wstatus);
		if (code == 130)
			printfd(2, "\n");
		if (code == 131)
			printfd(2, "Quit (core dumped)\n");
		if (pid == vars->last_pid)
			ret = code;
	}
	if (vars->command_was_built_in)
		return (g_exit_status);
	else
		return (ret);
}
