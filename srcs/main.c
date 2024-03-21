/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:46:32 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/21 17:45:22 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_exit_status;

int	main(int ac, char **av, char **env)
{
	t_vars	vars;

	init_minishell(&vars, env);
	get_paths(&vars);
	vars.dash_c = (ac == 3 && !ft_strcmp("-c", av[1]));
	while (1)
	{
		(set_signals(&vars), init_vars(&vars), update_rl_name(&vars));
		if (vars.dash_c)
			vars.line = ft_strdup(av[2]);
		else
			vars.line = readline(vars.readlinestring);
		if (!vars.line)
			break ;
		if (!vars.dash_c && !*vars.line)
			continue ;
		save_line(&vars);
		set_signals_cmd(&vars);
		if (parsing(&vars) != -1 && g_exit_status != 666)
			g_exit_status = exec(&vars);
		tok_clear(&vars.tokens);
		if (vars.dash_c)
			break ;
	}
	ft_exit((char *[2]){"exit", NULL}, &vars);
}
