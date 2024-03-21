/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:26:58 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/21 04:23:08 by legrandc         ###   ########.fr       */
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
