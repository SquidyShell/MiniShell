/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:46:32 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/12 21:38:06 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_exit_status;

int	main(int ac, char **av, char **env)
{
	t_vars	vars;

	((void)ac, (void)av);
	vars.env = env;
	vars.history = NULL;
	vars.tokens = NULL;
	vars.line = NULL;
	vars.env_list = create_env_list(env);
	get_paths(&vars);
	get_history();
	while (1)
	{
		init_vars(&vars);
		vars.line = readline(SQUIDYSHELL);
		if (!vars.line)
			break ;
		save_line(&vars);
		if (parsing(&vars) != -1 && vars.tokens)
			exec(&vars);
		dprintf(2, "%ld\n", vars.pipe_nb);
		tok_clear(&vars.tokens);
		vars.tokens = NULL;
	}
	append_to_history(&vars);
	free_matrix(vars.env_path);
	ft_lstclear(&vars.env_list, free);
}
