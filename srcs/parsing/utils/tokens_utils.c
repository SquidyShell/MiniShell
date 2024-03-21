/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:46:32 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/21 12:30:18 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*tok_new(char *content, size_t type)
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
	tok->is_double_quoted = 0;
	tok->is_single_quoted = 0;
	tok->hdc_file = NULL;
	return (tok);
}

void	tok_addback(t_tokens **tokens, t_vars *vars, t_tokens *new)
{
	if (!new)
		return (clean_vars(vars), exit(FAILURE));
	new->start = vars->index;
	if (!*tokens)
	{
		*tokens = new;
		(*tokens)->last = new;
		return ;
	}
	(*tokens)->last->next = new;
	(*tokens)->last = new;
	new->last = NULL;
}

void	tok_clear(t_tokens **tokens)
{
	t_tokens	*current;
	t_tokens	*next;

	if (!tokens)
		return ;
	current = *tokens;
	next = *tokens;
	while (next)
	{
		current = next;
		next = current->next;
		p_free(current->content);
		if (current->hdc_file)
		{
			unlink(current->hdc_file);
			p_free(current->hdc_file);
			current->hdc_file = NULL;
		}
		p_free(current);
	}
	*tokens = NULL;
}

static void	close_quoted_or_not_toks(t_vars *v)
{
	if (!v->tokens->last->is_single_quoted
		&& !v->tokens->last->is_double_quoted)
		v->tokens->last->content = ft_substr(v->line, v->tokens->last->start,
				v->index - v->tokens->last->start);
	else if (v->tokens->last->is_single_quoted
		&& v->tokens->last->is_double_quoted)
		v->tokens->last->content = substr_2s(v->line, v->tokens->last->start,
				v->index - v->tokens->last->start, "\"\'");
	else if (v->tokens->last->is_single_quoted)
		v->tokens->last->content = substr_s(v->line, v->tokens->last->start,
				v->index - v->tokens->last->start, '\'');
	else
		v->tokens->last->content = substr_s(v->line, v->tokens->last->start,
				v->index - v->tokens->last->start, '\"');
}

int	tok_close(t_vars *v)
{
	if (v->tokens && v->tokens->last->closed == false)
	{
		if (v->tokens->last->type == PIPE)
			v->pipe_nb++;
		v->tokens->last->closed = true;
		close_quoted_or_not_toks(v);
		if (!v->tokens->last->content)
			return (err_squid("Malloc", true), -1);
		if (v->tokens->last->error)
			return (berr(v->tokens->last->content, v), -1);
		if (v->tokens->last->type == HEREDOC_DELIM
			&& exec_heredoc(v->tokens->last, v))
			return (-1);
	}
	return (0);
}

// void	tok_print(t_tokens *tokens)
// {
// 	if (!tokens)
// 		return ;
// 	while (tokens)
// 	{
// 		printf("%sToken:%s %s, %sType:%s %zu, %sIs_in_quote?:%s %d\n", BLUE,
// 			RESET, tokens->content, GREEN, RESET, tokens->type, PINK, RESET,
// 			tokens->is_double_quoted);
// 		tokens = tokens->next;
// 	}
// }
