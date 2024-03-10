/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:46:32 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/10 18:49:14 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_exit_status;

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_vars	vars;

	((void)ac, (void)av);
	vars.env = env;
	vars.tokens = NULL;
	line = NULL;
	get_paths(&vars);
	while (1)
	{
		line = readline("\033[1;35mSquidyShell\033[0m$ ");
		if (!line)
			break ;
		parsing(&vars.tokens, line);
		tok_print(vars.tokens);
		exec(&vars);
		free(line);
		tok_clear(&vars.tokens);
		vars.tokens = NULL;
	}
	free_matrix(vars.env_path);
}
