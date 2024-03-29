/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 07:32:27 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/22 11:49:05 by legrandc         ###   ########.fr       */
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

static void	update_fd(int *fd, int fd2)
{
	ft_close(fd);
	*fd = fd2;
}

int	redirect(t_vars *vars)
{
	while (vars->cmd.token && vars->cmd.token->type != PIPE
		&& vars->cmd.token->type != AND_IF && vars->cmd.token->type != OR_IF)
	{
		if (vars->cmd.token->type == FILE_IN)
			update_fd(&vars->infile_fd, open(vars->cmd.token->content,
					O_RDONLY));
		else if (vars->cmd.token->type == FILE_OUT)
			update_fd(&vars->outfile_fd, open(vars->cmd.token->content,
					O_WRONLY | O_TRUNC | O_CREAT, 0666));
		else if (vars->cmd.token->type == DFILE_OUT)
			update_fd(&vars->outfile_fd, open(vars->cmd.token->content,
					O_WRONLY | O_APPEND | O_CREAT, 0666));
		else if (vars->cmd.token->type == HEREDOC_DELIM)
			update_fd(&vars->infile_fd, open(vars->cmd.token->hdc_file,
					O_RDONLY));
		if (vars->cmd.token->type == HEREDOC_DELIM && vars->infile_fd == -1)
			return (err_squid("Error retrieving heredoc file", 0), -1);
		if (vars->infile_fd == -1 || vars->outfile_fd == -1)
			return (err_squid(vars->cmd.token->content, true), -1);
		vars->cmd.token = vars->cmd.token->next;
	}
	dup2_and_close(&vars->infile_fd, STDIN_FILENO);
	dup2_and_close(&vars->outfile_fd, STDOUT_FILENO);
	return (0);
}
