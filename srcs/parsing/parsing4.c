/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:46:32 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/11 17:22:52 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Maniere cramptée, fonctions temporaires.
t_tokens	*tok_new_closed(char *content, size_t type)
{
	t_tokens	*tok;

	tok = malloc(sizeof(t_tokens));
	if (!tok)
		return (NULL);
	tok->content = content;
	tok->type = type;
	tok->closed = 1;
	tok->next = NULL;
	tok->error = false;
	return (tok);
}

int	not_in_quote(t_vars *v)
{
	if (is_whitespace(v->line[v->index]))
	{
		if (tok_close(v) == -1)
			return (-1);
	}
	else if (get_type_and_len(v) == -1)
		return (-1);
	return (1);
}