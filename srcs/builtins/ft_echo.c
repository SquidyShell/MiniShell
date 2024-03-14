/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:27:41 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/14 01:08:53 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **cmd, t_vars *vars)
{
	size_t	i;
	bool	print_endl;

	if (!cmd[1])
		return (printfd(STDIN, "\n"));
	print_endl = 0;
	i = 1;
	if (!ft_strcmp(cmd[1], "-n"))
	{
		print_endl = 1;
		i = 2;
	}
	while (cmd[i])
	{
		printfd(STDIN, "%s", cmd[i]);
		if (cmd[i + 1])
			printfd(STDIN, " ");
		i++;
	}
	if (!print_endl)
		printfd(STDIN, "\n");
	(void)vars;
}
