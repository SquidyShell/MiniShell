/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:15:49 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/15 08:56:15 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handler_sig(int sig)
{
	(void)sig;
	g_exit_status = 130;
	printfd(2, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	set_signals(t_vars *vars)
{
	(void)vars;
	signal(SIGINT, &handler_sig);
	signal(SIGQUIT, SIG_IGN);
}

static void	handler_sig_child(int sig)
{
	if (sig == SIGQUIT)
		g_exit_status = 132;
	else
		g_exit_status = 130;
}

void	set_signals_child(t_vars *vars)
{
	(void)vars;
	signal(SIGINT, &handler_sig_child);
	signal(SIGQUIT, &handler_sig_child);
}
