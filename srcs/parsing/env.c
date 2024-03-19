/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 06:09:09 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/19 12:03:35 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*create_env_list(char **env, bool *malloc_crampt)
{
	t_list	*env_list;
	size_t	i;

	env_list = NULL;
	i = 0;
	if (!env || !env[i])
		return (NULL);
	while (env[i])
	{
		ft_lstadd_back(&env_list, ft_lstnew(ft_strdup(env[i])));
		if (!ft_lstlast(env_list)->content)
			return (*malloc_crampt = 1, err_squid("Malloc", true),
				ft_lstclear(&env_list, free), NULL);
		i++;
	}
	return (env_list);
}

int	turn_env_into_char(t_vars *v)
{
	size_t	i;

	i = 0;
	free_matrix(v->env);
	v->env = malloc(sizeof(char *) * (ft_lstsize(v->env_list) + 1));
	if (!v->env)
		return (-1);
	while (v->env_list)
	{
		v->env[i++] = v->env_list->content;
		v->env_list = v->env_list->next;
	}
	v->env[i] = 0;
	return (0);
}
