/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:27:41 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/15 11:15:31 by cviegas          ###   ########.fr       */
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

size_t	count_char(char **cmd)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (cmd[i])
	{
		count += len(cmd[i]);
		if (cmd[i + 1])
			count++;
		i++;
	}
	return (count);
}

void	turn_args_in_buff(char buff[], char **args, bool endl)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (args[i])
	{
		ft_strlcpy(buff + j, args[i], len(args[i]) + 1);
		j += len(args[i]);
		if (args[i + 1])
			buff[j++] = ' ';
		i++;
	}
	if (endl)
		buff[j++] = '\n';
	buff[j] = 0;
}

void	ft_echo(char **cmd, t_vars *vars)
{
	char	buff[BUFF_SIZE];
	size_t	i;
	bool	print_endl;

	if (!cmd[1])
		return (printfd(STDOUT, "\n"));
	print_endl = 1;
	i = 0;
	while (cmd[++i])
	{
		if (is_option(cmd[i]))
			print_endl = 0;
		else
			break ;
	}
	if (count_char(cmd + i) + print_endl >= BUFF_SIZE)
		return (printfd(STDERR, "🦑: echo: string too long\n"));
	turn_args_in_buff(buff, cmd + i, print_endl);
	write(STDOUT, buff, len(buff));
	(void)vars;
}
