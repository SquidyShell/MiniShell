/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:31:25 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/13 15:42:52 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*smallest_above_list(t_list *env, char *previous)
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

static char	*find_min_list(t_list *env)
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

void	print_env_export_list(t_list *env)
{
	t_list	*current;
	char	*temp;

	if (!env)
		return ;
	current = env;
	temp = find_min_list(env);
	while (current)
	{
		if (temp[0] != '_' && temp[1] != '=')
			ft_printf("declare -x %s\n", temp);
		temp = smallest_above_list(env, temp);
		current = current->next;
	}
}
