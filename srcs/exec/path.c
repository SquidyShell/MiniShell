/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 07:45:02 by legrandc          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/03/14 22:10:13 by cviegas          ###   ########.fr       */
=======
/*   Updated: 2024/03/14 21:20:29 by legrandc         ###   ########.fr       */
>>>>>>> refs/remotes/origin/master
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
<<<<<<< HEAD
	ft_lstclear_no_free(&vars->last_command);
	// p_free(vars->cmd.path);
=======
	ft_lstclear(&vars->history, free);
	if (vars->cmd.path)
		free(vars->cmd.path);
>>>>>>> refs/remotes/origin/master
	if (vars->tokens)
		tok_clear(&vars->tokens);
	free_matrix(vars->env_path);
	free_matrix(vars->env);
}

void	search_and_execve(t_vars *vars)
{
	char	**args;

	args = vars->cmd.args;
	if (!args || get_path(args[0], vars) == -1)
		(clean_vars(vars), exit(EXIT_FAILURE));
	if (vars->cmd.path == NULL)
		printfd(STDERR_FILENO, "%s: command not found\n", args[0]);
	else if (access(vars->cmd.path, F_OK) == -1 && errno == ENOENT)
		perror(vars->cmd.path);
	else
	{
		execve(vars->cmd.path, args, vars->env);
		perror(vars->cmd.path);
		g_exit_status = 126;
	}
	free(args);
	clean_vars(vars);
	exit(g_exit_status);
}
