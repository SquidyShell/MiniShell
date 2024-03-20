/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:29:44 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/20 17:46:41 by legrandc         ###   ########.fr       */
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
	if (!(*nptr))
		return (0);
	while (*nptr)
	{
		if (!ft_isdigit(*nptr))
			return (0);
		if (sign == 1 && ret > (LLONG_MAX - (*nptr - '0')) / 10)
			return (0);
		if (sign == -1 && ret * sign < (LLONG_MIN + (*nptr - '0')) / 10)
			return (0);
		ret = ret * 10 + *nptr++ - '0';
	}
	*ptr = ret * sign;
	return (1);
}

void	ft_exit(char **cmd, t_vars *vars)
{
	long long	exit_code;
	bool		is_numeric;

	ft_close(&vars->old_stdout);
	append_to_history(vars);
	if (!vars->is_child)
		printfd(STDOUT, "exit\n");
	if (cmd[1])
	{
		exit_code = 0;
		is_numeric = ft_atoll_bool(cmd[1], &exit_code);
		if (cmd[2] && is_numeric)
			return (printfd(STDERR, "🦑: exit: too many arguments\n"));
		else
		{
			if (is_numeric)
				(clean_vars(vars), exit(exit_code % 256));
			else
				(printfd(STDERR, "🦑: exit: %s%s%s: numeric argument required\n",
						PINK, cmd[1], RESET), clean_vars(vars), exit(2));
		}
	}
	(clean_vars(vars), exit(g_exit_status));
}
