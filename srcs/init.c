/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 21:40:22 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/14 21:13:46 by legrandc         ###   ########.fr       */
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
	bool	does_malloc_crampt;

	vars->env = ft_strdup_matrix(env);
	if (!vars->env)
		exit(FAILURE);
	vars->env_list = create_env_list(env, &does_malloc_crampt);
	does_malloc_crampt = 0;
	if (does_malloc_crampt)
		(free_matrix(vars->env), exit(FAILURE));
	vars->history = NULL;
	vars->tokens = NULL;
	vars->line = NULL;
	vars->env_path = NULL;
	get_history();
	vars->exit_status = 0;
}
