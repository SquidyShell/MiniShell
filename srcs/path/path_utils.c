/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 06:39:45 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/20 16:35:21 by legrandc         ###   ########.fr       */
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
		p_free(t[i++]);
	p_free(t);
	t = NULL;
}

void	get_paths(t_vars *vars)
{
	char	**var;
	t_list	*env;

	vars->cmd.path = NULL;
	free_matrix(vars->env_path);
	vars->env_path = NULL;
	env = vars->env_list;
	while (env && env->content)
	{
		var = ft_split(env->content, '=');
		if (!var)
			(err_squid("Malloc error during path finding", 0), clean_vars(vars),
				exit(FAILURE));
		if (var[0] && var[1] && !ft_strcmp("PATH", var[0]))
		{
			vars->env_path = ft_split(var[1], ':');
			free_matrix(var);
			if (!vars->env_path)
				(err_squid("Malloc error during path finding", 0),
					clean_vars(vars), exit(FAILURE));
			break ;
		}
		env = env->next;
		free_matrix(var);
	}
}
