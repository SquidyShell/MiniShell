/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:46:32 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/11 18:15:07 by legrandc         ###   ########.fr       */
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
		vars->tokens->last = new;
		return ;
	}
	vars->tokens->last->next = new;
	vars->tokens->last = new;
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
	if (vars->tokens && vars->tokens->last->closed == false)
	{
		if (vars->tokens->last->type == PIPE)
			vars->pipe_nb++;
		vars->tokens->last->closed = true;
		if (!vars->tokens->last->is_single_quoted)
			vars->tokens->last->content = ft_substr(vars->line,
					vars->tokens->last->start, vars->index
					- vars->tokens->last->start);
		else
			vars->tokens->last->content = ft_substr(vars->line,
					vars->tokens->last->start, vars->index
					- vars->tokens->last->start);
		if (!vars->tokens->last->content)
			return (ft_printfd(STDERR_FILENO, "Malloc error\n"), -1);
		if (vars->tokens->last->error)
			return (berr(vars->tokens->last->content), -1);
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
