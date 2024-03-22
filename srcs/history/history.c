/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:18:24 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/22 00:27:15 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_history_name(t_vars *vars)
{
	bool	malloc_crampted;
	char	*ret;

	ret = search_var_in_env(vars, "HOME", &malloc_crampted);
	if (malloc_crampted)
		err_squid("malloc error, could not get history", false);
	return (ret);
}

void	get_history(t_vars *vars)
{
	char	*s;
	int		fd;
	char	*history;
	char	*path_to_history;

	vars->history = NULL;
	history = get_history_name(vars);
	path_to_history = ft_strjoin(history, "/" HISTORY_NAME);
	if (!path_to_history)
		return ;
	fd = open(path_to_history, O_RDONLY);
	free(path_to_history);
	free(history);
	if (fd == -1)
		return ;
	while (1)
	{
		s = gnl_no_nl(fd);
		if (!s)
			break ;
		add_history(s);
		free(s);
	}
	ft_close(&fd);
}

int	save_line(t_vars *vars)
{
	t_list	*new;

	add_history(vars->line);
	new = ft_lstnew(vars->line);
	if (!new)
		return (err_squid("Malloc", true), -1);
	if (!vars->history)
		vars->history = new;
	else
		vars->last_command->next = new;
	vars->last_command = new;
	return (0);
}

void	append_to_history(t_vars *vars)
{
	int		fd;
	t_list	*next;
	char	*history;
	char	*path_to_history;

	history = get_history_name(vars);
	path_to_history = ft_strjoin(history, "/" HISTORY_NAME);
	if (!path_to_history)
		return ;
	fd = open(path_to_history, O_WRONLY | O_APPEND | O_CREAT, 0600);
	free(path_to_history);
	free(history);
	if (fd == -1)
		return (err_squid("could not append to history", false));
	while (vars->history)
	{
		next = vars->history->next;
		printfd(fd, "%s\n", vars->history->content);
		free(vars->history->content);
		free(vars->history);
		vars->history = next;
	}
	ft_close(&fd);
}
