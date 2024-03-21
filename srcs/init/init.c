/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 21:40:22 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/21 19:49:23 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_vars(t_vars *v)
{
	v->index = 0;
	v->in_quote = 0;
	v->in_dquote = 0;
	v->in_expanded_var = 0;
	v->end_of_var = 0;
	v->command_was_built_in = 0;
	v->tokens = NULL;
	v->cmd.args = NULL;
	v->fildes[0] = -2;
	v->fildes[1] = -2;
	if (g_exit_status == 666)
		g_exit_status = 130;
	v->last_token_type = 0;
}

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
		new[i] = matrix[i];
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
		printfd(2, "squidyshell-init: " DIR_ERROR GETCWD_ERROR " %s\n",
			strerror(errno));
	}
	else
	{
		pwd = ft_strjoin("PWD=", dir);
		if (!pwd || maybe_add_to_env(pwd, vars) == -1)
			err_squid("squidyshell-init: Malloc error, PWD will not be set", 0);
		free(dir);
		free(pwd);
	}
}

void	init_minishell(t_vars *vars, char **env)
{
	bool	does_malloc_crampt;

	if (env)
	{
		vars->env = ft_strdup_matrix(env);
		if (!vars->env)
			(err_squid("Maloc error", 0), exit(EXIT_FAILURE));
	}
	does_malloc_crampt = 0;
	vars->env_list = create_env_list(env, &does_malloc_crampt);
	if (does_malloc_crampt)
		(p_free(vars->env), exit(FAILURE));
	vars->history = NULL;
	vars->tokens = NULL;
	vars->line = NULL;
	vars->env_path = NULL;
	vars->old_stdout = 0;
	vars->readlinestring = NULL;
	set_pwd(vars);
	get_history(vars);
	g_exit_status = 0;
	vars->old_stdout = -2;
	vars->old_stdin = -2;
	vars->cmd.args = NULL;
	vars->is_child = false;
}
