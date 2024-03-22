/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:26:58 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/21 15:29:25 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	hderr(size_t line_nb, char *limiter)
{
	g_exit_status = 0;
	printfd(STDERR,
		SQUID HDERR_0 PINK "%zu" RESET HDERR_1 PINK "%s" RESET "')\n", line_nb,
		limiter);
}

bool	is_there_delimiter(char *line, char *limiter, size_t limiter_len)
{
	return (!ft_strncmp(line, limiter, limiter_len) && line[limiter_len] == 0);
}

void	heredoc_handler(int sig)
{
	(void)sig;
	close(STDIN_FILENO);
	write(1, "\n", 1);
	g_exit_status = 666;
}

bool	hd_needs_to_expand(char *line, size_t i)
{
	return (line[i] == '$' && line[i + 1] && !is_whitespace(line[i + 1])
		&& is_snakecase_or_qmark(line[i + 1]));
}
