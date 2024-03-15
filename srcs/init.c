/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 21:40:22 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/15 23:37:33 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_strdup_matrix(char **matrix)
{
	char	**new;
	size_t	i;

	i = 0;
	while (matrix[i])
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (matrix[i])
	{
		new[i] = ft_strdup(matrix[i]);
		if (!new[i])
			return (free_matrix(new), NULL);
		i++;
	}
	new[i] = 0;
	return (new);
}

static void	set_pwd(t_vars *vars)
{
	char	*dir;
	char	*pwd;

	dir = ft_getcwd();
	if (!dir)
	{
		g_exit_status = 1;
		printfd(2, "squidyshell-init: " GETCWD_ERROR " %s\n", strerror(errno));
	}
	else
	{
		pwd = ft_strjoin("PWD=", dir);
		if (!pwd || maybe_add_to_env(pwd, vars) == -1)
			perr("squidyshell-init: Malloc error, PWD will not be set");
		free(dir);
		free(pwd);
	}
}

void	init_minishell(t_vars *vars, char **env)
{
	bool	does_malloc_crampt;

	vars->env = ft_strdup_matrix(env);
	if (!vars->env)
		exit(FAILURE);
	does_malloc_crampt = 0;
	vars->env_list = create_env_list(env, &does_malloc_crampt);
	if (does_malloc_crampt)
		(free_matrix(vars->env), exit(FAILURE));
	vars->history = NULL;
	vars->tokens = NULL;
	vars->line = NULL;
	vars->env_path = NULL;
	vars->old_stdout = 0;
	set_pwd(vars);
	get_history(vars);
	g_exit_status = 0;
}
