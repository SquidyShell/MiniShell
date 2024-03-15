/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 06:09:09 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/15 21:35:14 by cviegas          ###   ########.fr       */
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
	t_list	*current;
	char	*env_line;

	var_value = NULL;
	current = v->env_list;
	*malloc_crampt = 0;
	while (current)
	{
		env_line = current->content;
		if (!ft_strncmp(var_to_find, env_line, ft_strlen(var_to_find)))
		{
			if (env_line[ft_strlen(var_to_find)] == '=')
			{
				var_value = ft_substr(env_line, ft_strlen(var_to_find) + 1,
						ft_strlen(env_line) - (ft_strlen(var_to_find) + 1));
				if (!var_value)
					return (*malloc_crampt = 1, NULL);
				break ;
			}
		}
		current = current->next;
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
	new_line[0] = 0;
	i = -1;
	while (++i < (int)v->index)
		new_line[i] = old_line[i];
	j = 0;
	if (var_value)
		while (var_value[j])
			new_line[i++] = var_value[j++];
	v->end_of_var = i;
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
	if (v->line_was_expanded)
		p_free(v->line);
	v->line = new_line_expanded(v, var_value, var_name_len, line_temp);
	if (!v->line)
		return (-1);
	v->line_was_expanded = true;
	free(line_temp);
	return (1);
}

int	expand_this_shit(t_vars *v)
{
	char	*var_to_find;
	char	*var_value;
	bool	malloc_crampt;

	v->in_expanded_var = 1;
	if (v->line[v->index + 1] == '?')
	{
		if (var_is_exit_status(v) == -1)
			return (-1);
	}
	else
	{
		var_to_find = whats_the_var(v->line, v->index);
		if (!var_to_find)
			return (perr("Malloc"), -1);
		var_value = search_var_in_env(v, var_to_find, &malloc_crampt);
		if (malloc_crampt)
			return (free(var_to_find), perr("Malloc"), -1);
		if (replace_var_name_by_value(v, var_value, len(var_to_find)) == -1)
			return (free(var_value), free(var_to_find), perr("Malloc"), -1);
		free(var_value);
		free(var_to_find);
	}
	v->index -= 1;
	return (0);
}
