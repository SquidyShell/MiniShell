/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:29:44 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/15 11:04:36 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_isspace(int c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

bool	ft_atoll_bool(const char *nptr, long long *ptr)
{
	long long	ret;
	int			sign;

	ret = 0;
	sign = 1;
	while (is_whitespace(*nptr))
		nptr++;
	if (*nptr == '+')
		nptr++;
	else if (*nptr == '-' && ++nptr)
		sign = -1;
	if (!ft_isdigit(*nptr))
		return (*ptr = ret * sign, 0);
	while (*nptr)
	{
		if (!ft_isdigit(*nptr))
			return (1);
		if (sign == 1 && ret > (LLONG_MAX - (*nptr - '0')) / 10)
			return (0);
		if (sign == -1 && ret > (LLONG_MIN + (*nptr - '0')) / 10)
			return (0);
		ret = ret * 10 + *nptr - '0';
		nptr++;
	}
	*ptr = ret * sign;
	return (1);
}

void	ft_exit(char **cmd, t_vars *vars)
{
	long long	exit_code;

	exit_code = 0;
	// close(vars->old_stdout);
	printf("Debug: cmd[1] = %s\n", cmd[0]);
	clean_vars(vars);
	ft_atoll_bool(cmd[1], &exit_code);
	printfd(STDERR, "Debug: cmd[1] = %s\n", cmd[1]);
	printfd(STDOUT, "exit\n");
	if (cmd[1])
	{
		if (cmd[2])
			return (free(cmd), printfd(STDERR,
					"🦑: exit: too many arguments\n"));
		else
		{
			if (ft_atoll_bool(cmd[1], &exit_code))
				(free(cmd), exit(exit_code % 256));
			else
			{
				printfd(STDERR, "Debug: cmd[1] = %s\n", cmd[1]);
				printfd(STDERR, "🦑: exit: %s%s%s: numeric argument required\n",
					PINK, cmd[1], RESET);
			}
		}
	}
	(free(cmd), exit(vars->exit_status));
}
