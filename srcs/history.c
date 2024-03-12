/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:18:24 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/12 20:47:37 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_history(void)
{
	char	*s;
	int		fd;

	fd = open(".squidyshell_history", O_RDONLY);
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
	close(fd);
}

int	save_line(t_vars *vars)
{
	t_list	*new;

	add_history(vars->line);
	new = ft_lstnew(vars->line);
	if (!new)
		return (perr("Malloc error"), -1);
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

	fd = open(".squidyshell_history", O_WRONLY | O_APPEND | O_CREAT);
	if (fd == -1)
		return ;
	while (vars->history)
	{
		next = vars->history->next;
		printfd(fd, "%s\n", vars->history->content);
		free(vars->history);
		vars->history = next;
	}
	close(fd);
}
