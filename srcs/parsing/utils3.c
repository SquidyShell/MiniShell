/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 03:57:52 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/17 04:10:48 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	err_squid(const char *s, bool print_strerrno)
{
	if (!print_strerrno)
		printfd(STDERR, SQUID "%s\n", s);
	else
		printfd(STDERR, SQUID "%s: %s\n", s, strerror(errno));
}