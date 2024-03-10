/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:46:32 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/10 17:51:15 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	berr(char *token)
{
	ft_printfd(STDERR_FILENO,
		"%s%sbash:%s syntax error near unexpected token `%s%s%s'\n", BOLD, RED,
		RESET, PINK, token, RESET);
}

void	s(void)
{
	printf("%s%sSQUID%s\n", BOLD, GREEN, RESET);
}

int	is_metachar(t_tokens token)
{
	return (token.type >= 1 && token.type <= 7);
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
