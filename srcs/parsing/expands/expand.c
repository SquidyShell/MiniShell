/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 06:09:09 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/21 21:16:48 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
					return (err_squid("Malloc error during env searching", 0),
						*malloc_crampt = 1, NULL);
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
		return (err_squid("Malloc error during expansion", 0), NULL);
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
	free(line_temp);
	if (!v->line)
		return (-1);
	v->line_was_expanded = true;
	return (1);
}

static int	general_case(t_vars *v)
{
	char	*to_find;
	char	*value;
	bool	malloc_crampt;

	to_find = whats_the_var(v->line, v->index);
	if (!to_find)
		return (err_squid("Malloc", true), -1);
	value = search_var_in_env(v, to_find, &malloc_crampt);
	if (malloc_crampt)
		return (free(to_find), -1);
	if (!value && v->tokens && (v->tokens->last->type == LESS
			|| v->tokens->last->type == GREAT
			|| v->tokens->last->type == DGREAT))
		return (free(to_find), err_squid("ambiguous redirect", 0), -1);
	if (replace_var_name_by_value(v, value, len(to_find)) == -1)
		return (free(value), free(to_find), -1);
	free(value);
	free(to_find);
	return (0);
}

int	expand_this_shit(t_vars *v)
{
	v->in_expanded_var = 1;
	if (v->line[v->index + 1] == '?')
	{
		if (var_is_exit_status(v) == -1)
			return (-1);
	}
	else if (general_case(v) == -1)
		return (-1);
	v->index -= 1;
	return (0);
}
