/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:46:32 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/10 18:27:41 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_vars	vars;

	(void)ac;
	(void)av;
	line = NULL;
	vars.envp = envp;
	vars.tokens = NULL;
	while (1)
	{
		line = readline(SQUIDYSHELL);
		if (!line)
			break ;
		if (check_syntax(line))
		{
			parsing(&vars.tokens, line);
			tok_print(vars.tokens);
		}
		free(line);
		tok_clear(&vars.tokens);
	}
}
