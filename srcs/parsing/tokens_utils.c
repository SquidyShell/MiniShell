/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:46:32 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/11 17:56:05 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_tokens	*tok_new(char *content, size_t type)
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
	tok->is_double_quoted = 0;
	tok->is_single_quoted = 1;
	return (tok);
}

void	tok_addback(t_vars *vars, t_tokens *new)
{
	new->start = vars->index;
	if (!vars->tokens)
	{
		vars->tokens = new;
		vars->last_token = new;
		return ;
	}
	vars->last_token->next = new;
	vars->last_token = new;
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
		free(current->content);
		free(current);
	}
	*tokens = NULL;
}

int	tok_close(t_vars *vars)
{
	if (vars->tokens && vars->last_token->closed == false)
	{
		if (vars->last_token->type == PIPE)
			vars->pipe_nb++;
		vars->last_token->closed = true;
		if (!vars->last_token->is_single_quoted)
			vars->last_token->content = ft_substr(vars->line,
					vars->last_token->start, vars->index
					- vars->last_token->start);
		else
			vars->last_token->content = ft_substr_skip(vars->line,
					vars->last_token->start, vars->index
					- vars->last_token->start, '\'');
		if (!vars->last_token->content)
			return (ft_printfd(STDERR_FILENO, "Malloc error\n"), -1);
		if (vars->last_token->error)
			return (berr(vars->last_token->content), -1);
	}
	return (0);
}

void	tok_print(t_tokens *tokens)
{
	while (tokens)
	{
		printf("%sToken:%s %s, %sType:%s %zu\n", BLUE, RESET, tokens->content,
			GREEN, RESET, tokens->type);
		tokens = tokens->next;
	}
}
