/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 17:58:12 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/21 17:32:32 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_commands(t_vars *vars)
{
	int	nl;

	nl = 0;
	while (1)
	{
		vars->pid = wait(&vars->wstatus);
		if (vars->pid == -1)
			break ;
		if (WIFSIGNALED(vars->wstatus) && WTERMSIG(vars->wstatus) + 128 == 130
			&& !nl && ++nl)
			printfd(2, "\n");
		if (vars->pid != vars->last_pid)
			continue ;
		if (WIFEXITED(vars->wstatus))
			vars->code = WEXITSTATUS(vars->wstatus);
		else
		{
			vars->code = 128 + WTERMSIG(vars->wstatus);
			if (vars->code == 131)
				printfd(2, "Quit (core dumped)\n");
		}
		g_exit_status = vars->code;
	}
	return (g_exit_status);
}
