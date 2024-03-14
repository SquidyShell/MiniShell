/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:27:41 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/14 20:39:36 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_option(char *cmd)
{
	if (*cmd++ != '-')
		return (false);
	while (*cmd)
		if (*cmd++ != 'n')
			return (false);
	return (true);
}

void	ft_echo(char **cmd, t_vars *vars)
{
	size_t	i;
	bool	print_endl;

	if (!cmd[1])
		return (printfd(STDIN, "\n"));
	print_endl = 1;
	i = 0;
	while (cmd[++i])
	{
		if (is_option(cmd[i]))
			print_endl = 0;
		else
			break ;
	}
	while (cmd[i])
	{
		printfd(STDOUT, "%s", cmd[i]);
		if (cmd[i + 1])
			printfd(STDOUT, " ");
		i++;
	}
	if (print_endl)
		printfd(STDOUT, "\n");
	(void)vars;
}
