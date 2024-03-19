/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:26:58 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/19 19:25:37 by cviegas          ###   ########.fr       */
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

void static	write_heredoc(t_tokens *tok, t_vars *v)
{
	char	*line;
	char	*new_line;
	size_t	line_nb;
	bool	malloc_crampted;

	line = NULL;
	line_nb = 1;
	malloc_crampted = 0;
	new_line = NULL;
	while (1)
	{
		(printfd(STDERR, "> "), line = get_next_line(STDIN));
		if (!line)
			hderr(line_nb, tok->content);
		if (!line || is_there_delimiter(line, tok->content, len(tok->content)))
			break ;
		if (!tok->is_double_quoted && !tok->is_single_quoted)
			if (expand_line(line, &new_line, v) == -1 && ++malloc_crampted)
				break ;
		(printfd(tok->end_heredoc[WRITE], new_line), free(new_line),
			p_free(line), line_nb++);
	}
	(p_free(line), close(tok->end_heredoc[WRITE]),
		close(tok->end_heredoc[READ]), clean_vars(v));
	exit(malloc_crampted);
}

int	exec_heredoc(t_tokens *tok, t_vars *v)
{
	int	pid;
	int	wstatus;

	if (pipe(tok->end_heredoc) < 0)
		return (err_squid("Pipe", true), -1);
	pid = fork();
	if (pid == 0)
		write_heredoc(tok, v);
	wait(&wstatus);
	close(tok->end_heredoc[WRITE]);
	if (WIFEXITED(wstatus))
	{
		if (wstatus != 0)
			return (err_squid("Malloc error during here_doc initilization", 0),
				clean_vars(v), -1);
	}
	else
		return (write(2, "\n", 1), -1);
	return (0);
}
