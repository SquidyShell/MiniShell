/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 21:40:22 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/13 13:32:08 by cviegas          ###   ########.fr       */
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

void	init_minishell(t_vars *vars, char **env)
{
	vars->env = ft_strdup_matrix(env);
	if (!vars->env)
		exit(FAILURE);
	vars->env_list = create_env_list(env);
	if (!vars->env_list)
		(free_matrix(vars->env), exit(FAILURE));
	vars->history = NULL;
	vars->tokens = NULL;
	vars->line = NULL;
}
