/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:46:32 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/11 13:02:16 by legrandc         ###   ########.fr       */
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
		vars->last_token->closed = true;
		vars->last_token->content = ft_substr(vars->line,
				vars->last_token->start, vars->index - vars->last_token->start);
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
