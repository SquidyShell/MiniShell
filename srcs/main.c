/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:46:32 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/20 12:26:20 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_exit_status;

int	main(int ac, char **av, char **env)
{
	t_vars	vars;

	((void)ac, (void)av);
	init_minishell(&vars, env);
	get_paths(&vars);
	while (1)
	{
		set_signals(&vars);
		init_vars(&vars);
		vars.line = readline(SQUIDYSHELL);
		if (!vars.line)
			break ;
		set_signals_cmd(&vars);
		save_line(&vars);
		if (parsing(&vars) != -1 && g_exit_status != 666)
		{
			tok_print(vars.tokens);
			if (vars.line_was_expanded)
				free(vars.line);
			if (vars.tokens)
				g_exit_status = exec(&vars);
		}
		tok_clear(&vars.tokens);
	}
	ft_exit((char *[2]){"exit", NULL}, &vars);
}
