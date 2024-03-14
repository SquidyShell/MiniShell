/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 17:58:12 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/14 13:50:32 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_commands(t_vars *vars)
{
	int	ret;
	int	signal;
	int	pid;
	int	wstatus;

	while (1)
	{
		pid = wait(&wstatus);
		if (pid == -1)
			break ;
		if (WIFEXITED(wstatus))
			signal = WEXITSTATUS(wstatus);
		else
			signal = 128 + WTERMSIG(wstatus);
		if (signal == 130)
			printfd(2, "\n");
		if (signal == 131)
			printfd(2, "Quit (core dumped)\n");
		if (pid == vars->last_pid)
			ret = signal;
	}
	return (ret);
}
