/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:46:32 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/16 02:48:03 by cviegas          ###   ########.fr       */
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

void	s(void)
{
	ft_printfd(2, "%s%sSQUID%s\n", BOLD, GREEN, RESET);
}

// void	syntax_error(t_tokens *tokens)
// {
// 	if (!tokens->next)
// 		berr("newline", v);
// 	else if (tokens->next->type == AND_IF)
// 		berr("`&&'");
// 	else if (tokens->next->type == OR_IF)
// 		berr("||");
// 	else if (tokens->next->type == LESS)
// 		berr("<");
// 	else if (tokens->next->type == GREAT)
// 		berr(">");
// 	else if (tokens->next->type == DLESS)
// 		berr("<<");
// 	else if (tokens->next->type == DGREAT)
// 		berr(">>");
// }

int	is_metachar(t_tokens token)
{
	return ((token.type >= 1 && token.type <= 7));
}

bool	is_tok_symbol(t_tokens token)
{
	return ((token.type >= 1 && token.type <= 7) || (token.type >= 14
			&& token.type <= 15));
}
