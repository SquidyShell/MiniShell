/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 22:48:09 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/16 14:56:27 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_ignore_lvl(size_t *ignore_lvl, size_t type)
{
	if (*ignore_lvl)
	{
		if (type == PARENTHESES_IN)
			(*ignore_lvl)++;
		else if (type == PARENTHESES_OUT)
			(*ignore_lvl)--;
	}
}
