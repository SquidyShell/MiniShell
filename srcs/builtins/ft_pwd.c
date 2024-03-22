/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:27:58 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/22 13:24:49 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Behavior of bash posix 5.1.16 where the command fails when getcwd fails,
in oppistion to bash where it would just print the PWD variable from before*/

void	ft_pwd(char **cmd, t_vars *vars)
{
	char	*dir;

	(void)cmd;
	(void)vars;
	dir = ft_getcwd();
	if (!dir)
	{
		g_exit_status = 1;
		(void)printfd(2, "pwd: " DIR_ERROR GETCWD_ERROR " %s\n",
			strerror(errno));
	}
	else
		printf("%s\n", dir);
	free(dir);
}
