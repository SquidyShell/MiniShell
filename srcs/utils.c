/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 06:39:45 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/14 19:53:02 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_matrix(char **t)
{
	size_t	i;

	if (!t)
		return ;
	i = 0;
	while (t[i])
		free(t[i++]);
	free(t);
	t = NULL;
}

void	get_paths(t_vars *vars)
{
	char	**var;
	char	**env;

	vars->cmd.path = NULL;
	vars->env_path = NULL;
	env = vars->env;
	if (!env[0])
		return ;
	while (env)
	{
		var = ft_split(*env, '=');
		if (var[0] && var[1] && !ft_strcmp("PATH", var[0]))
		{
			vars->env_path = ft_split(var[1], ':');
			free_matrix(var);
			break ;
		}
		env++;
		free_matrix(var);
	}
	g_exit_status = 127;
}
