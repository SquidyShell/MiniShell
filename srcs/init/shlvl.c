/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:00:09 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/22 11:24:56 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	case_num(t_vars *vars, char *shlvl)
{
	char	*new_shlvl;
	int		val;

	val = ft_atoi(shlvl);
	free(shlvl);
	if (val >= 1000)
	{
		val = 0;
		err_squid("squidyshell-init: warning: shell level \
too high, resetting to 1", 0);
	}
	else if (val < 0)
		val = -1;
	new_shlvl = ft_itoa(val + 1);
	shlvl = ft_strjoin("SHLVL=", new_shlvl);
	if (!shlvl || maybe_add_to_env(shlvl, vars) == -1)
		err_squid("squidyshell-init: Malloc error, SHLVL will not be set", 0);
	free(shlvl);
	free(new_shlvl);
}

void	get_shlvl(t_vars *vars)
{
	bool	malloc_crampted;
	char	*shlvl;

	shlvl = search_var_in_env(vars, "SHLVL", &malloc_crampted);
	if (malloc_crampted)
		return (err_squid("malloc error, shlvl not set", false));
	if (!shlvl)
	{
		shlvl = ft_strjoin("SHLVL=", "1");
		if (!shlvl || maybe_add_to_env(shlvl, vars) == -1)
			err_squid("squidyshell-init: Malloc error, SHLVL will not be set",
				0);
		free(shlvl);
	}
	else
	{
		case_num(vars, shlvl);
	}
}
