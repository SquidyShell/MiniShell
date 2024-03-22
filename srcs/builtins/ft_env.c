/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:29:06 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/22 10:44:15 by legrandc         ###   ########.fr       */
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
		if (there_is_this_char(var, '='))
		{
			printf("%s\n", var);
		}
		current = current->next;
	}
}

void	ft_env(char **cmd, t_vars *vars)
{
	if (cmd[1])
		return (printfd(STDERR, "🦑: subject says \"%s%s%sC\"\n", PINK,
				"with no options or arguments", RESET));
	print_env(vars->env_list);
}
