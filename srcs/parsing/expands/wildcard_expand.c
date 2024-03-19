/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 06:09:09 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/19 12:31:34 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_matching(const char *pattern, const char *filename)
{
	if (*pattern == 0)
		return (*filename == 0);
	if (*pattern == '*')
	{
		if (is_matching(pattern + 1, filename))
			return (1);
		return (*filename != 0 && is_matching(pattern, filename + 1));
	}
	if (*pattern == *filename)
		return (is_matching(pattern + 1, filename + 1));
	return (0);
}

bool	is_expandable(t_tokens *prev, t_tokens *curr)
{
	return ((curr->type == WORD || curr->type == FILE_IN
			|| curr->type == FILE_OUT || curr->type == DFILE_OUT)
		&& !curr->is_double_quoted && !curr->is_single_quoted
		&& prev->type != AND_IF && prev->type != OR_IF
		&& there_is_this_char(curr->content, '*'));
}

int	maybe_expand(t_tokens *curr)
{
	char			*new;
	DIR				*dir;
	struct dirent	*file;
	size_t			i;
	size_t			nb_expands;

	dir = opendir(".");
	i = 0;
	nb_expands = 0;
	while (dir)
	{
		file = readdir(dir);
		if (!file)
			break ;
		if ((file->d_type == 8 || file->d_type == 4) && *file->d_name != '.')
		{
			if (is_matching(curr->content, file->d_name))
			{
				if (nb_expands == 0)
				{
					p_free(curr->content);
					curr->content = ft_strdup(file->d_name);
					if (!curr->content)
						return (-1);
				}
				else
				{
					new = ft_strdup(file->d_name);
					if (!new)
						return (-1);
					if (tok_add_inbetween(curr, curr->next, tok_new(ft_strdup)))
					// Ajoute un token entre curr et curr->next avec comme type le type de curr
					// et comme content file->d_name
				}
			}
		}
	}
	if (dir)
		closedir(dir);
}

int	parse_tokens(t_vars *v, t_tokens *tok)
{
	t_tokens	*prev;
	t_tokens	*curr;

	if (!tok->next)
		return (0);
	prev = tok;
	while (prev->next)
	{
		curr = prev->next;
		if (is_expandable(prev, curr))
		{
			if (maybe_expand(curr) == -1)
				return (-1);
		}
		prev = curr;
	}
	return (0);
}
