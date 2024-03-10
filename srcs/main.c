/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:46:32 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/10 19:14:00 by cviegas          ###   ########.fr       */
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
		line = readline(SQUIDYSHELL);
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
