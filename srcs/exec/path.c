/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 07:45:02 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/15 23:32:36 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	p_free(void *p)
{
	if (p)
	{
		free(p);
		p = NULL;
	}
}

void	clean_vars(t_vars *vars)
{
	ft_lstclear(&vars->env_list, free);
	ft_lstclear(&vars->history, free);
	p_free(vars->cmd.path);
	if (vars->tokens)
		tok_clear(&vars->tokens);
	free_matrix(vars->env_path);
	free_matrix(vars->env);
	p_free(vars->cmd.args);
}

void	search_and_execve(t_vars *vars)
{
	char	**args;

	args = vars->cmd.args;
	if (!args || get_path(args[0], vars) == -1)
		(clean_vars(vars), exit(EXIT_FAILURE));
	if (vars->cmd.path == NULL)
		printfd(STDERR, "%s: command not found\n", args[0]);
	else if (access(vars->cmd.path, F_OK) == -1 && errno == ENOENT)
		perror(vars->cmd.path);
	else
	{
		execve(vars->cmd.path, args, vars->env);
		perror(vars->cmd.path);
		g_exit_status = 126;
	}
	clean_vars(vars);
	exit(g_exit_status);
}
