/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_rl_name.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 06:39:45 by cviegas          #+#    #+#             */
/*   Updated: 2024/03/20 15:13:33 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_git_r(int end[2], char *git_r, t_vars *v)
{
	pid_t	child_searching;
	int		status;

	if (pipe(end) < 0)
		return (err_squid("Pipe", true), -1);
	child_searching = fork();
	if (child_searching < 0)
		return (close(end[1]), close(end[2]), err_squid("Pipe", true), -1);
	if (!child_searching)
	{
		(dup2(end[WRITE], STDOUT), close(end[READ]), close(end[WRITE]));
		execve("/usr/bin/git", (char *[4]){"git", "remote", "-v", NULL},
			v->env);
		(clean_vars(v), exit(EXIT_FAILURE));
	}
	else
	{
		close(end[WRITE]);
		waitpid(child_searching, &status, 0);
		(read(end[READ], git_r, 100), close(end[READ]));
	}
	if (status)
		return (0);
	return (1);
}

int	get_git_b(int end[2], char *git_b, t_vars *v)
{
	pid_t	child_searching;
	int		status;

	if (pipe(end) < 0)
		return (err_squid("Pipe", true), -1);
	child_searching = fork();
	if (child_searching < 0)
		return (close(end[1]), close(end[2]), err_squid("Pipe", true), -1);
	if (!child_searching)
	{
		(dup2(end[WRITE], STDOUT), close(end[READ]), close(end[WRITE]));
		execve("/usr/bin/git", (char *[5]){"git", "rev-parse", "--abbrev-ref",
			"HEAD", NULL}, v->env);
		(clean_vars(v), exit(FAILURE));
	}
	else
	{
		close(end[WRITE]);
		waitpid(child_searching, &status, 0);
		(read(end[READ], git_b, 100), close(end[READ]));
	}
	if (status)
		return (0);
	return (1);
}
