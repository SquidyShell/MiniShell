/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:15:49 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/13 20:43:25 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handler_sig(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_status = 130;
		printfd(2, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	set_signals(t_vars *vars)
{
	struct sigaction	sa;

	(void)vars;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = &handler_sig;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

static void	handler_sig_child(int sig)
{
	if (sig == SIGQUIT)
		g_exit_status = 132;
	else
		g_exit_status = 130;
	exit(g_exit_status);
}

void	set_signals_child(t_vars *vars)
{
	struct sigaction	sa;

	(void)vars;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = &handler_sig_child;
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
}
