/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:28:24 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/12 17:52:07 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*smallest_above(t_list *env, char *previous)
{
	t_list	*temp;
	char	*min;

	temp = env;
	min = 0;
	while (temp)
	{
		if (ft_strcmp((char *)temp->content, previous) > 0)
		{
			if (!min)
				min = temp->content;
			else if (ft_strcmp(temp->content, min) < 0)
				min = temp->content;
		}
		temp = temp->next;
	}
	return (min);
}

char	*find_min(t_list *env)
{
	t_list	*temp;
	char	*min;

	if (!env)
		return (NULL);
	temp = env;
	min = temp->content;
	while (temp)
	{
		if (ft_strcmp(temp->content, min) < 0)
			min = temp->content;
		temp = temp->next;
	}
	return (min);
}

void	print_env_export(t_list *env)
{
	t_list	*current;
	char	*temp;

	if (!env)
		return ;
	current = env;
	temp = find_min(env);
	while (current)
	{
		if (temp[0] != '_' && temp[1] != '=')
			ft_printf("declare -x %s\n", temp);
		temp = smallest_above(env, temp);
		current = current->next;
	}
}

void	ft_export(char **cmd, t_vars *vars)
{
	if (!cmd[1])
		print_env_export(vars->env_list);
}
