/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 21:40:22 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/12 21:45:33 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_minishell(t_vars *vars, char **env)
{
	vars->env = env;
	vars->history = NULL;
	vars->tokens = NULL;
	vars->line = NULL;
	vars->env_list = create_env_list(env);
}
