/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 06:39:45 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/15 21:20:31 by legrandc         ###   ########.fr       */
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
	t_list	*env;

	vars->cmd.path = NULL;
	free_matrix(vars->env_path);
	vars->env_path = NULL;
	env = vars->env_list;
	while (env && env->content)
	{
		var = ft_split(env->content, '=');
		if (var[0] && var[1] && !ft_strcmp("PATH", var[0]))
		{
			vars->env_path = ft_split(var[1], ':');
			free_matrix(var);
			break ;
		}
		env = env->next;
		free_matrix(var);
	}
}
