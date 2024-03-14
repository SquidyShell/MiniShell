/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:28:42 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/14 00:30:07 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_var(t_list **env, bool first, t_list *prev_curr_next[3])
{
	if (first)
	{
		if (prev_curr_next[2]->content)
		{
			(*env) = (*env)->next;
			ft_lstdelone(prev_curr_next[1], free);
		}
	}
	else
	{
		ft_lstdelone(prev_curr_next[1], free);
		if (prev_curr_next[2])
			prev_curr_next[0]->next = prev_curr_next[2];
		else
			prev_curr_next[0]->next = NULL;
	}
}

bool	its_this_var(char *content, char *arg)
{
	return (!ft_strncmp(arg, content, len(arg)) && (content[len(arg)] == '='
			|| !content[len(arg)]));
}

void	there_is_only_one_var(t_list **env, char *arg)
{
	if (ft_lstsize(*env) == 1)
	{
		if (its_this_var((*env)->content, arg))
			ft_lstclear(env, free);
	}
}

void	delete_var_if_exists(t_list **env, char *arg)
{
	t_list	*next;
	t_list	*prev;
	t_list	*curr;
	bool	first;

	if (!ft_lstsize(*env))
		return ;
	if (ft_lstsize(*env) == 1)
		return (there_is_only_one_var(env, arg));
	curr = *env;
	if (its_this_var(curr->next->content, arg))
		return (delete_var(env, 0, (t_list *[]){curr, curr->next,
				curr->next->next}));
	prev = curr;
	first = 1;
	while (curr)
	{
		next = curr->next;
		if (its_this_var(curr->content, arg))
			return (delete_var(env, first, (t_list *[]){prev, curr, next}));
		prev = prev->next;
		curr = prev->next;
		if (first)
			first = 0;
	}
}

void	ft_unset(char **cmd, t_vars *vars)
{
	size_t	i;

	if (!cmd[1])
		return ;
	i = 1;
	while (cmd[i])
		delete_var_if_exists(&vars->env_list, cmd[i++]);
}
