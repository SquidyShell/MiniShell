/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 07:32:27 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/20 02:21:26 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_fds(t_vars *vars)
{
	if (vars->cmd_i)
	{
		dup2_and_close(&vars->last_fd, STDIN_FILENO);
	}
	if (vars->cmd_i != vars->pipe_nb)
	{
		dup2_and_close(&vars->fildes[1], STDOUT_FILENO);
		ft_close(&vars->fildes[0]);
	}
}

int	redirect(t_vars *vars)
{
	while (vars->cmd.token && vars->cmd.token->type != PIPE)
	{
		if (vars->cmd.token->type == FILE_IN)
			vars->infile_fd = open(vars->cmd.token->content, O_RDONLY);
		else if (vars->cmd.token->type == FILE_OUT)
			vars->outfile_fd = open(vars->cmd.token->content,
					O_WRONLY | O_TRUNC | O_CREAT, 0666);
		else if (vars->cmd.token->type == DFILE_OUT)
			vars->outfile_fd = open(vars->cmd.token->content,
					O_WRONLY | O_APPEND | O_CREAT, 0666);
		else if (vars->cmd.token->type == HEREDOC_DELIM)
			vars->infile_fd = vars->cmd.token->end_heredoc[0];
		if (vars->infile_fd == -1 || vars->outfile_fd == -1)
			return (printfd(2, SQUID "%s: %s\n", vars->cmd.token->content,
					strerror(errno)), -1);
		vars->cmd.token = vars->cmd.token->next;
	}
	dup2_and_close(&vars->infile_fd, STDIN_FILENO);
	dup2_and_close(&vars->outfile_fd, STDOUT_FILENO);
	return (0);
}

// if (vars->cmd.token->type == HEREDOC_DELIM)
// 	(dup2_and_close(vars->cmd.token->end_heredoc[READ], STDIN), is_heredoc = 1);
