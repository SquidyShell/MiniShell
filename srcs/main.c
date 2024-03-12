/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:46:32 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/12 17:24:50 by cviegas          ###   ########.fr       */
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
	vars.env_list = create_env_list(env);
	get_paths(&vars);
	while (1)
	{
		init_vars(&vars);
		vars.line = readline(SQUIDYSHELL);
		if (!vars.line)
			break ;
		if (parsing(&vars) != -1 && vars.tokens)
			(free(vars.line), exec(&vars));
		dprintf(2, "%ld\n", vars.pipe_nb);
		tok_clear(&vars.tokens);
		vars.tokens = NULL;
	}
	free_matrix(vars.env_path);
}
