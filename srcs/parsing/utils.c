/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:46:32 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/09 11:44:33 by cviegas          ###   ########.fr       */
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
