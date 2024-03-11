/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:46:32 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/11 16:26:54 by cviegas          ###   ########.fr       */
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

void	if_quote(t_vars *v)
{
	v->index++;
	v->close_index = v->index;
	while (v->line[v->close_index] != '\'')
		v->close_index++;
	tok_addback(v, tok_new_closed(ft_substr(v->line, v->index, v->close_index
				- v->index), WORD));
	v->index = v->close_index;
}
