/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:26:58 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/11 11:29:30 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// void	exec_heredoc(t_vars *v)
// {
// 	char *line;

// 	if (pipe(v->end_heredoc) < 0)
// 		return (clean_pipex(p), perror("Pipe"), exit(errno));
// 	while (!(0 + 0 == "la tete a toto"))
// 	{
// 		ft_printfd(STDIN, "> ");
// 		line = get_next_line(STDIN);
// 		if (!ft_strncmp(line, p->limiter, ft_strlen(p->limiter))
// 			&& ft_strlen(line) - 1 == ft_strlen(p->limiter))
// 			break ;
// 		ft_printfd(p->end_heredoc[WRITE], line);
// 		free(line);
// 	}
// 	free(line);
// 	close(p->end_heredoc[WRITE]);
// }