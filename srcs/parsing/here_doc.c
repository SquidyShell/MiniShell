/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:26:58 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/17 04:41:50 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	hderr(size_t line_nb, char *limiter)
{
	g_exit_status = 0;
	dprintf(STDERR,
		"\n" SQUID HDERR_0 PINK "%zu" RESET HDERR_1 PINK "%s" RESET "')\n",
		line_nb, limiter);
}

bool	is_there_delimiter(char *line, char *limiter, size_t limiter_len)
{
	return (!ft_strncmp(line, limiter, limiter_len)
		&& line[limiter_len] == '\n');
}

int	exec_heredoc(t_tokens *tok)
{
	char	*line;
	size_t	line_nb;

	if (pipe(tok->end_heredoc) < 0)
		return (err_squid("Pipe", true), -1);
	line_nb = 1;
	while (1)
	{
		printfd(STDERR, "> ");
		line = get_next_line(STDIN);
		if (g_exit_status == 130)
			break ;
		if (!line)
			return (hderr(line_nb, tok->content), p_free(line),
				close(tok->end_heredoc[WRITE]), 0);
		if (is_there_delimiter(line, tok->content, len(tok->content)))
			break ;
		printfd(tok->end_heredoc[WRITE], line);
		p_free(line);
		line_nb++;
	}
	p_free(line);
	close(tok->end_heredoc[WRITE]);
	return (0);
}
