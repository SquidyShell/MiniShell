/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 06:09:09 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/21 11:26:44 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_matching(const char *pattern, const char *filename)
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

bool	is_expandable(t_tokens *curr)
{
	return ((curr->type == WORD || curr->type == FILE_IN
			|| curr->type == FILE_OUT || curr->type == DFILE_OUT)
		&& !curr->is_double_quoted && !curr->is_single_quoted
		&& there_is_this_char(curr->content, '*'));
}

static int	maybe_turn_file_into_tok(struct dirent *file, t_tokens *curr,
		char *pattern, bool *already_expanded)
{
	char		*new;
	t_tokens	*tok_new;

	if (is_matching(pattern, file->d_name))
	{
		if (!(*already_expanded))
		{
			(p_free(curr->content), curr->content = ft_strdup(file->d_name));
			if (!curr->content)
				return (-1);
			*already_expanded = true;
		}
		else
		{
			new = ft_strdup(file->d_name);
			if (!new)
				return (-1);
			tok_new = tok_new_quoted(new, curr->type, 0, 0);
			if (tok_add_inbetween(&curr, &tok_new) == -1)
				return (free(new), -1);
			curr = curr->next;
		}
	}
	return (0);
}

int	maybe_expand(t_tokens *curr)
{
	DIR				*dir;
	struct dirent	*file;
	char			*pattern;
	bool			already_expanded;

	already_expanded = false;
	dir = opendir(".");
	if (!dir)
		return (0);
	pattern = ft_strdup(curr->content);
	if (!pattern)
		return (closedir(dir), -1);
	while (dir)
	{
		file = readdir(dir);
		if (!file)
			break ;
		if (*file->d_name != '.' || *curr->content == '.')
		{
			if (maybe_turn_file_into_tok(file, curr, pattern,
					&already_expanded) == -1)
				return (p_free(pattern), -1);
		}
	}
	return (closedir(dir), p_free(pattern), 0);
}
