/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:46:32 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/19 23:35:28 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	berr(char *token, t_vars *v)
{
	(void)v;
	g_exit_status = 2;
	printfd(STDERR, "🦑: syntax error near unexpected token `%s%s%s'\n", PINK,
		token, RESET);
}

void	eof_err(char *match, t_vars *v)
{
	(void)v;
	g_exit_status = 2;
	printfd(STDERR, "🦑: unexpected EOF while looking for matching `%s%s%s'\n%s",
		PINK, match, RESET, EOF_ERR);
}

void	ft_close(int *fd)
{
	if (*fd > 2)
		close(*fd);
	*fd = -2;
}

int	is_metachar(t_tokens token)
{
	return ((token.type >= 1 && token.type <= 7));
}

bool	is_tok_symbol(t_tokens token)
{
	return ((token.type >= 1 && token.type <= 7) || token.type == PARENTHESES_IN
		|| token.type == PARENTHESES_OUT);
}
