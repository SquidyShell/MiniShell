/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 06:09:09 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/20 19:44:39 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*create_env_list(char **env, bool *malloc_crampt)
{
	t_list	*env_list;
	int		i;
	t_list	*new;
	char	*new_content;

	env_list = NULL;
	i = -1;
	if (!env || !env[0])
		return (NULL);
	while (env[++i])
	{
		new_content = ft_strdup(env[i]);
		if (!new_content)
			return (*malloc_crampt = 1, err_squid("Malloc", true),
				ft_lstclear(&env_list, free), NULL);
		new = ft_lstnew(new_content);
		if (!new)
			return (*malloc_crampt = 1, err_squid("Malloc", true),
				ft_lstclear(&env_list, free), p_free(new_content), NULL);
		ft_lstadd_back(&env_list, new);
		if (!ft_lstlast(env_list)->content)
			return (*malloc_crampt = 1, err_squid("Malloc", true),
				ft_lstclear(&env_list, free), NULL);
	}
	return (env_list);
}

int	turn_env_into_char(t_vars *v)
{
	size_t	i;
	t_list	*curr;

	i = 0;
	p_free(v->env);
	curr = v->env_list;
	v->env = malloc(sizeof(char *) * (ft_lstsize(v->env_list) + 1));
	if (!v->env)
		return (-1);
	while (curr)
	{
		v->env[i++] = curr->content;
		curr = curr->next;
	}
	v->env[i] = 0;
	return (0);
}
