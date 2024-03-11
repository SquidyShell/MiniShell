/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:46:32 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/11 17:12:22 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_exit_status;

int	main(int ac, char **av, char **env)
{
	t_vars	vars;

	((void)ac, (void)av);
	vars.env = env;
	vars.tokens = NULL;
	vars.line = NULL;
	get_paths(&vars);
	while (1)
	{
		vars.pipe_nb = 0;
		vars.cmd_i = 0;
		vars.index = 0;
		vars.line = readline(SQUIDYSHELL);
		if (!vars.line)
			break ;
		if (parsing(&vars) != -1 && vars.tokens)
			exec(&vars);
		dprintf(2, "%ld\n", vars.pipe_nb);
		free(vars.line);
		tok_clear(&vars.tokens);
		vars.tokens = NULL;
	}
	free_matrix(vars.env_path);
}
