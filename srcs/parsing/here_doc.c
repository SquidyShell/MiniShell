/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:26:58 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/16 17:44:44 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	hderr(size_t line_nb, char *limiter)
{
	g_exit_status = 0;
	dprintf(STDERR, "%s%s%zu%s%s%s%s%s')\n", HDERR_0, PINK, line_nb, RESET,
		HDERR_1, PINK, limiter, RESET);
}

int	exec_heredoc(t_tokens *tok)
{
	char	*line;
	size_t	line_nb;

	if (pipe(tok->end_heredoc) < 0)
		return (perror("Pipe"), -1);
	line_nb = 1;
	g_exit_status == 0;
	while (1 || ++line_nb)
	{
		printfd(STDERR, "> ");
		line = get_next_line(STDIN);
		if (g_exit_status == 130)
			break ;
		if (!line || g_exit_status == 128)
			return (hderr(line_nb, tok->content), p_free(line),
				close(tok->end_heredoc[WRITE]), 0);
		if (!ft_strcmp(line, tok->content) && len(line) == len(tok->content))
			break ;
		printfd(tok->end_heredoc[WRITE], line);
		p_free(line);
	}
	p_free(line);
	close(tok->end_heredoc[WRITE]);
	return (0);
}
