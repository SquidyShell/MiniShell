/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 06:09:09 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/20 19:44:02 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_var_in_env_hd(t_vars *v, char *var_to_find, bool *malloc_crampt)
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

char	*new_line_expanded_hd(size_t index, char *value, size_t var_name_len,
		char *old_line)
{
	char	*new_line;
	int		i;
	int		j;

	new_line = malloc(sizeof(char) * (len(old_line) - var_name_len + len(value)
				- +1));
	if (!new_line)
		return (err_squid("Malloc error during heredoc initilization", 0),
			NULL);
	new_line[0] = 0;
	i = -1;
	while (++i < (int)index)
		new_line[i] = old_line[i];
	j = 0;
	if (value)
		while (value[j])
			new_line[i++] = value[j++];
	j = index + var_name_len + 1;
	while (old_line[j])
		new_line[i++] = old_line[j++];
	new_line[i] = 0;
	return (new_line);
}

int	replace_var_name_by_value_hd(size_t *i, char **line, char *value,
		size_t var_name_len)
{
	char	*temp;

	temp = ft_strdup(*line);
	if (!temp)
		return (-1);
	p_free(*line);
	*line = new_line_expanded_hd(*i, value, var_name_len, temp);
	if (!*line)
		return (p_free(temp), -1);
	*i += len(value);
	p_free(temp);
	return (1);
}

int	expand_this_shit_hd(char **new_line, size_t *index, t_vars *v)
{
	char	*to_find;
	char	*value;
	bool	malloc_crampt;

	value = NULL;
	if ((*new_line)[(*index) + 1] == '?')
	{
		if (var_is_exit_status_hd(new_line, index) == -1)
			return (-1);
	}
	else
	{
		to_find = whats_the_var(*new_line, *index);
		if (!to_find)
			return (err_squid("Malloc", true), -1);
		value = search_var_in_env_hd(v, to_find, &malloc_crampt);
		if (malloc_crampt)
			return (free(to_find), err_squid("Malloc", true), -1);
		if (replace_var_name_by_value_hd(index, new_line, value,
				len(to_find)) == -1)
			(free(value), free(to_find), clean_vars(v), exit(FAILURE));
		free(value);
		free(to_find);
	}
	return (0);
}

int	var_is_exit_status_hd(char **new_line, size_t *i)
{
	char	*value;

	value = ft_itoa(g_exit_status);
	if (!value)
		return (err_squid("Malloc", true), -1);
	if (replace_var_name_by_value_hd(i, new_line, value, 1) == -1)
		return (free(value), err_squid("Malloc", true), -1);
	free(value);
	return (1);
}
