/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:46:32 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/10 18:24:32 by cviegas          ###   ########.fr       */
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