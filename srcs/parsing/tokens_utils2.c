/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:29:12 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/17 03:38:05 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_tokens	*tok_new_quoted(char *content, size_t type, bool s_quote,
		bool d_quote)
{
	t_tokens	*tok;

	tok = malloc(sizeof(t_tokens));
	if (!tok)
		return (NULL);
	tok->content = content;
	tok->type = type;
	tok->closed = 0;
	tok->next = NULL;
	tok->error = false;
	tok->is_single_quoted = s_quote;
	tok->is_double_quoted = d_quote;
	return (tok);
}

bool	tok_close_and_addback(t_tokens **tokens, t_vars *vars, int type)
{
	if (tok_close(vars) == -1)
		return (0);
	tok_addback(tokens, vars, tok_new_quoted(NULL, type, vars->in_quote,
			vars->in_dquote));
	return (1);
}

bool	tok_addback_and_close(t_tokens **tokens, t_vars *vars, int type)
{
	tok_addback(tokens, vars, tok_new_quoted(NULL, type, vars->in_quote,
			vars->in_dquote));
	if (tok_close(vars) == -1)
		return (0);
	return (1);
}
