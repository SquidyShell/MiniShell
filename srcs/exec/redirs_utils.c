/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 08:52:45 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/13 07:43:31 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dup2_and_close(int fd1, int fd2)
{
	if (fd1 != -1)
	{
		dup2(fd1, fd2);
		close(fd1);
	}
	return (0);
}
