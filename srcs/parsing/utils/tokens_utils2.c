/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:29:12 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/21 19:27:44 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_tokens	*tok_new_quoted(char *content, size_t type, bool s_quote,
		bool d_quote)
{
	t_tokens	*tok;

	tok = malloc(sizeof(t_tokens));
	if (!tok)
		return (err_squid("Malloc error during parsing", 0), NULL);
	tok->content = content;
	tok->type = type;
	tok->closed = 0;
	tok->next = NULL;
	tok->error = false;
	tok->is_single_quoted = s_quote;
	tok->is_double_quoted = d_quote;
	tok->hdc_file = NULL;
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

int	tok_add_inbetween(t_tokens **first, t_tokens **new)
{
	t_tokens	*temp;

	if (!new)
		return (-1);
	temp = (*first)->next;
	(*first)->next = (*new);
	(*new)->next = temp;
	return (0);
}
