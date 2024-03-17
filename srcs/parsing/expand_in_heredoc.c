/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_in_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 06:09:09 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/17 05:44:25 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	var_is_exit_status(t_vars *v)
{
	char	*var_value;

	var_value = ft_itoa(g_exit_status);
	if (!var_value)
		return (err_squid("Malloc", true), -1);
	if (replace_var_name_by_value(v, var_value, 1) == -1)
		return (free(var_value), err_squid("Malloc", true), -1);
	free(var_value);
	return (1);
}

int	expand_line(char *line)
{
	return (0);
}