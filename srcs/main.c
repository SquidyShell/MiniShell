/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:46:32 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/15 12:11:43 by cviegas          ###   ########.fr       */
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
		save_line(&vars);
		if (parsing(&vars) != -1 && vars.tokens)
			vars.exit_status = exec(&vars);
		tok_clear(&vars.tokens);
		vars.tokens = NULL;
	}
	append_to_history(&vars);
	ft_lstclear(&vars.env_list, free);
	free_matrix(vars.env_path);
	free_matrix(vars.env);
	return (vars.exit_status);
}
