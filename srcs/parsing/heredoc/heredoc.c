/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:26:58 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/20 17:34:49 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	heredoc_handler(int sig)
{
	(void)sig;
	close(STDIN_FILENO);
	write(1, "\n", 1);
	g_exit_status = 666;
}

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

int static	write_heredoc(t_tokens *tok, t_vars *v)
{
	while (g_exit_status != 666)
	{
		v->hdc.line = readline("> ");
		if (!v->hdc.line && g_exit_status != 666)
			hderr(v->hdc.line_nb, tok->content);
		if (!v->hdc.line || is_there_delimiter(v->hdc.line, tok->content,
				len(tok->content)))
			break ;
		if (!tok->is_double_quoted && !tok->is_single_quoted)
			if (expand_line(v->hdc.line, &v->hdc.new_line, v) == -1
				&& ++v->hdc.malloc_crampted)
				break ;
		(printfd(tok->end_heredoc[WRITE], v->hdc.new_line),
			free(v->hdc.new_line), p_free(v->hdc.line), v->hdc.line_nb++);
		write(tok->end_heredoc[WRITE], "\n", 1);
	}
	ft_close(&tok->end_heredoc[WRITE]);
	close(STDIN_FILENO);
	p_free(v->hdc.line);
	dup2(v->old_stdin, STDIN_FILENO);
	close(v->old_stdin);
	return ((v->hdc.malloc_crampted == 0) - 1);
}

int	exec_heredoc(t_tokens *tok, t_vars *v)
{
	v->hdc.line = NULL;
	v->hdc.line_nb = 1;
	v->hdc.malloc_crampted = 0;
	v->hdc.new_line = NULL;
	v->old_stdin = dup(STDIN_FILENO);
	if (v->old_stdin == -1)
		return (err_squid("dup()", true), -1);
	if (pipe(tok->end_heredoc) < 0)
		return (err_squid("Pipe", true), -1);
	signal(SIGINT, &heredoc_handler);
	if (write_heredoc(tok, v) == -1)
		return (clean_vars(v), -1);
	return (0);
}
