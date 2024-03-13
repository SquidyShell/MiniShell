/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:28:42 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/13 22:34:29 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_var(t_list **env, bool first, t_list *prev_curr_next[3])
{
	if (first)
	{
		ft_lstdelone(prev_curr_next[1], free);
		prev_curr_next[0]->next = prev_curr_next[2];
	}
	else
	{
		(*env) = (*env)->next;
		ft_lstdelone(prev_curr_next[1], free);
	}
}

void	delete_var_if_exists(t_list **env, char *arg)
{
	char	*content;
	t_list	*next;
	t_list	*previous;
	t_list	*current;
	bool	first;

	first = 1;
	previous = *env;
	current = previous;
	while (current)
	{
		next = current->next;
		content = (char *)current->content;
		if (!ft_strncmp(arg, content, ft_strlen(arg))
			&& (content[ft_strlen(arg)] == '=' || !content[ft_strlen(arg)]))
			return (delete_var(env, first, (t_list *[]){previous, current,
					next}));
		previous = previous->next;
		current = previous->next;
		if (first)
			first = 0;
	}
}

void	ft_unset(char **cmd, t_vars *vars)
{
	size_t	i;

	if (!cmd[0])
		return ;
	i = 0;
	while (cmd[i])
		delete_var_if_exists(&vars->env_list, cmd[i++]);
}
