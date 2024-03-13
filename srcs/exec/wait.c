/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 17:58:12 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/10 18:25:09 by legrandc         ###   ########.fr       */
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
	return (ret);
}
