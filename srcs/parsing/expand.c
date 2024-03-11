/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 06:09:09 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/11 22:52:01 by cviegas          ###   ########.fr       */
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

char	*search_var_in_env(t_vars *v, char *var_to_find, bool *malloc_crampt)
{
	char	*var_value;
	size_t	i;

	var_value = NULL;
	i = 0;
	while (v->env[i])
	{
		if (!ft_strncmp(var_to_find, v->env[i], ft_strlen(var_to_find)))
		{
			if (v->env[i][ft_strlen(var_to_find)] == '=')
			{
				var_value = ft_substr(v->env[i], ft_strlen(var_to_find) + 1,
						ft_strlen(v->env[i]) - (ft_strlen(var_to_find) + 1));
				if (!var_value)
					return (*malloc_crampt = 1, NULL);
				break ;
			}
		}
		i++;
	}
	return (var_value);
}

char	*new_line_expanded(t_vars *v, char *var_value, size_t var_name_len,
		char *old_line)
{
	char	*new_line;
	int		i;
	int		j;

	new_line = malloc(sizeof(char) * (len(old_line) - var_name_len
				+ len(var_value) + 1));
	if (!new_line)
		return (NULL);
	i = -1;
	while (++i < (int)v->index)
		new_line[i] = old_line[i];
	j = 0;
	if (var_value)
		while (var_value[j])
			new_line[i++] = var_value[j++];
	j = (int)v->index + var_name_len + 1;
	while (old_line[j])
		new_line[i++] = old_line[j++];
	new_line[i] = 0;
	return (new_line);
}

int	replace_var_name_by_value(t_vars *v, char *var_value, size_t var_name_len)
{
	char	*line_temp;

	line_temp = ft_strdup(v->line);
	if (!line_temp)
		return (-1);
	free(v->line);
	v->line = NULL;
	v->line = new_line_expanded(v, var_value, var_name_len, line_temp);
	if (!v->line)
		return (-1);
	free(line_temp);
	return (1);
}

int	expand_this_shit(t_vars *v)
{
	char	*var_to_find;
	char	*var_value;
	bool	malloc_crampt;

	malloc_crampt = 0;
	var_to_find = whats_the_var(v->line, v->index);
	if (!var_to_find)
		return (perr("Malloc"), -1);
	var_value = search_var_in_env(v, var_to_find, &malloc_crampt);
	if (malloc_crampt)
		return (free(var_to_find), perr("Malloc"), -1);
	if (!replace_var_name_by_value(v, var_value, len(var_to_find)))
		return (free(var_to_find), free(var_value), perr("Malloc"), -1);
	free(var_to_find);
	free(var_value);
	return (1);
}
