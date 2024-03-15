/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:29:06 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/15 14:59:27 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_list *env)
{
	t_list	*current;
	char	*var;

	if (!env)
		return ;
	current = env;
	while (current)
	{
		var = (char *)current->content;
		if (there_is_an_equal(var))
		{
			if (var[0] == '_' && var[1] == '=')
				printf("_=/usr/bin/env\n");
			else
				printf("%s\n", var);
		}
		current = current->next;
	}
}

void	ft_env(char **cmd, t_vars *vars)
{
	if (cmd[1])
		return (printfd(STDERR, "🦑: subject says \"%s%s%s\"\n", PINK,
				"with no options or arguments", RESET));
	print_env(vars->env_list);
}
