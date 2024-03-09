/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:46:32 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/09 11:02:56 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(void)
{
	char		*line;
	t_tokens	*tokens;

	line = NULL;
	tokens = NULL;
	while (1)
	{
		line = readline("\033[1;35mSquidyShell\033[0m$ ");
		if (!line)
			break ;
		parsing(&tokens, line);
		tok_print(tokens);
		free(line);
	}
	tok_clear(&tokens);
}
