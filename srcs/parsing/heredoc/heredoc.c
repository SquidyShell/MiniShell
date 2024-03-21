/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:26:58 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/21 21:16:35 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_hd_name(t_tokens *tok)
{
	int		fd;
	char	buff[257];
	size_t	length;
	int		fd_file;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1)
		return (-1);
	length = 0;
	while (length != 257)
	{
		if (read(fd + length, buff, 1) == -1)
			return (-1);
		buff[length] = 48 + (unsigned char)buff[length] % (126 - 48);
		buff[length + 1] = 0;
		tok->hdc_file = ft_strjoin("/tmp/", buff);
		fd_file = open(tok->hdc_file, O_RDWR | O_CREAT | O_EXCL, 0600);
		if (fd_file != -1)
			return (ft_close(&fd), fd_file);
		free(tok->hdc_file);
		length++;
	}
	return (ft_close(&fd), -1);
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
		if (hd_needs_to_expand(*new_line, i))
		{
			if (expand_this_shit_hd(new_line, &i, v) == -1)
				return (-1);
		}
		else
			i++;
	}
	return (0);
}

static int	write_heredoc(t_tokens *tok, t_vars *v, int fd)
{
	while (g_exit_status != 666)
	{
		v->hdc.line = readline("> ");
		if (!v->hdc.line && g_exit_status != 666)
			hderr(v->hdc.line_nb, tok->content);
		if (!v->hdc.line || is_there_delimiter(v->hdc.line, tok->content,
				len(tok->content)))
			break ;
		if (!tok->is_double_quoted && !tok->is_single_quoted
			&& expand_line(v->hdc.line, &v->hdc.new_line, v) == -1
			&& ++v->hdc.malloc_crampted)
			break ;
		else if (tok->is_double_quoted || tok->is_single_quoted)
			v->hdc.new_line = ft_strdup(v->hdc.line);
		(printfd(fd, v->hdc.new_line), free(v->hdc.new_line),
			p_free(v->hdc.line), v->hdc.line_nb++);
		write(fd, "\n", 1);
	}
	close(fd);
	close(STDIN_FILENO);
	p_free(v->hdc.line);
	dup2(v->old_stdin, STDIN_FILENO);
	close(v->old_stdin);
	return ((v->hdc.malloc_crampted == 0) - 1);
}

int	exec_heredoc(t_tokens *tok, t_vars *v)
{
	int	fd;

	if (needs_to_remove_quotes(tok) && maybe_remove_quotes(tok) == -1)
		return (-1);
	v->hdc.line = NULL;
	v->hdc.line_nb = 1;
	v->hdc.malloc_crampted = 0;
	v->hdc.new_line = NULL;
	v->old_stdin = dup(STDIN_FILENO);
	if (v->old_stdin == -1)
		return (err_squid("dup()", true), -1);
	fd = find_hd_name(tok);
	signal(SIGINT, &heredoc_handler);
	if (write_heredoc(tok, v, fd) == -1)
		return (clean_vars(v), -1);
	return (0);
}
