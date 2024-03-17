/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:26:58 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/17 09:03:05 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	needs_to_expand(char *line, size_t i)
{
	return (line[i] == '$' && line[i + 1] && !is_whitespace(line[i + 1])
		&& is_snakecase_or_qmark(line[i + 1]));
}

int	expand_line(char *line, char **new_line, t_vars *v)
{
	size_t	i;

	*new_line = ft_strdup(line);
	if (!*new_line)
		return (-1);
	if (!*new_line[0] || *new_line[0] == '\n')
		return (0);
	i = 0;
	while ((*new_line)[i])
	{
		if (needs_to_expand(*new_line, i))
		{
			if (expand_this_shit_hd(new_line, &i, v) == -1)
				return (-1);
		}
		else
			i++;
	}
	return (0);
}

void	init_values(char **line, size_t *nb)
{
	*line = NULL;
	*nb = 1;
}

int	exec_heredoc(t_tokens *tok, t_vars *v)
{
	char	*line;
	char	*new_line;
	size_t	line_nb;

	if (pipe(tok->end_heredoc) < 0)
		return (err_squid("Pipe", true), -1);
	init_values(&new_line, &line_nb);
	while (1)
	{
		(printfd(STDERR, "> "), line = get_next_line(STDIN));
		if (!line)
			return (hderr(line_nb, tok->content),
				close(tok->end_heredoc[WRITE]), 0);
		if (g_exit_status == 130 || is_there_delimiter(line, tok->content,
				len(tok->content)))
			break ;
		if (!tok->is_double_quoted && !tok->is_single_quoted)
			if (expand_line(line, &new_line, v) == -1)
				return (p_free(new_line), p_free(line),
					close(tok->end_heredoc[WRITE]), -1);
		(printfd(tok->end_heredoc[WRITE], new_line), free(new_line),
			p_free(line), line_nb++);
	}
	(p_free(line), close(tok->end_heredoc[WRITE]));
	return (0);
}
