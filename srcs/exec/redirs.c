/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 07:32:27 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/13 14:15:48 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_fds(t_vars *vars)
{
	if (vars->cmd_i)
		dup2_and_close(vars->last_fd, STDIN_FILENO);
	if (vars->cmd_i != vars->pipe_nb)
	{
		dup2_and_close(vars->fildes[1], STDOUT_FILENO);
		close(vars->fildes[0]);
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
		vars->cmd.token = vars->cmd.token->next;
	}
	dup2_and_close(vars->infile_fd, STDIN_FILENO);
	dup2_and_close(vars->outfile_fd, STDOUT_FILENO);
	return (0);
}
