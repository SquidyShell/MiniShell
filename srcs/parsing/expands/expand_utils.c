/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 18:03:51 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/22 16:04:26 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*whats_the_var(char *line, size_t index)
{
	size_t	i;

	i = index + 1;
	while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
		i++;
	return (ft_substr(line, index + 1, i - index - 1));
}
