/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:22:45 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/21 12:26:48 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	needs_to_remove_quotes(t_tokens *tok)
{
	return (tok->content && (there_is_this_char(tok->content, '"')
			|| there_is_this_char(tok->content, '\'')));
}

/* ft_strdup but skips if s[to_skip] */
static char	*strdup_skip(char const *s, bool *to_skip)
{
	char	*dupskipping;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
		i++;
	dupskipping = malloc((i + 1) * sizeof(char));
	if (!dupskipping)
		return (NULL);
	i = 0;
	j = 0;
	while (s[j])
	{
		if (!to_skip[j])
			dupskipping[i++] = s[j];
		j++;
	}
	dupskipping[i] = 0;
	return (dupskipping);
}

static int	realloc_content_without_quotes(t_tokens *tok, bool *to_skip)
{
	char	*temp;

	temp = ft_strdup(tok->content);
	if (!temp)
		return (-1);
	free(tok->content);
	tok->content = strdup_skip(temp, to_skip);
	if (!tok->content)
		return (free(tok->content), -1);
	return (free(temp), 0);
}

void	is_there_some_quote(t_tokens *tok, t_v2i *quotes, bool *to_skip,
		size_t i)
{
	if (tok->content[i] == '"' && !(*quotes)[0])
	{
		if (!(*quotes)[1])
			(*quotes)[1] = true;
		else
			(*quotes)[1] = false;
		to_skip[i] = true;
	}
	if (tok->content[i] == '\'' && !(*quotes)[1])
	{
		if (!(*quotes)[0])
			(*quotes)[0] = true;
		else
			(*quotes)[0] = false;
		to_skip[i] = true;
	}
}

int	maybe_remove_quotes(t_tokens *tok)
{
	t_v2i	quote_dquote;
	bool	*to_skip;
	size_t	i;

	quote_dquote = (t_v2i){0, 0};
	i = 0;
	to_skip = malloc(len(tok->content));
	if (!to_skip)
		return (-1);
	ft_bzero(to_skip, len(tok->content));
	while (tok->content[i])
	{
		is_there_some_quote(tok, &quote_dquote, to_skip, i);
		i++;
	}
	if (realloc_content_without_quotes(tok, to_skip) == -1)
		return (free(to_skip), -1);
	return (free(to_skip), 0);
}
