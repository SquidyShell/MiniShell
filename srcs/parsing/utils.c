/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:46:32 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/10 19:16:35 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	berr(char *token)
{
	ft_printfd(2, "🦑: syntax error near unexpected token `%s%s%s'\n", PINK,
		token, RESET);
}

void	s(void)
{
	ft_printfd(2, "%s%sSQUID%s\n", BOLD, GREEN, RESET);
}

void	syntax_error(t_tokens *tokens)
{
	if (!tokens->next)
		berr("newline");
	else if (tokens->next->type == AND_IF)
		berr("`&&'");
	else if (tokens->next->type == OR_IF)
		berr("||");
	else if (tokens->next->type == LESS)
		berr("<");
	else if (tokens->next->type == GREAT)
		berr(">");
	else if (tokens->next->type == DLESS)
		berr("<<");
	else if (tokens->next->type == DGREAT)
		berr(">>");
}

int	is_metachar(t_tokens token)
{
	return (token.type >= 1 && token.type <= 7);
}
