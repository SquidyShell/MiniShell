/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:28:24 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/13 20:47:16 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_correct_arg(char *cmd)
{
	size_t	i;

	if (ft_isdigit(cmd[0]))
		return (0);
	i = 0;
	while (cmd[i] && cmd[i] != '=')
	{
		if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

bool	var_is_already_in_env(char *line, t_list *env)
{
	char	*content;
	size_t	equal_index;

	equal_index = 0;
	while (line[equal_index] && line[equal_index] != '=')
		equal_index++;
	while (env)
	{
		content = (char *)env->content;
		if (!ft_strncmp(line, content, equal_index)
			&& (content[equal_index] == '=' || !content[equal_index]))
			return (1);
		env = env->next;
	}
	return (0);
}

int	replace_the_var(t_list **env, char *line)
{
	char	*content;
	t_list	*current;
	size_t	equal_index;

	equal_index = 0;
	while (line[equal_index] && line[equal_index] != '=')
		equal_index++;
	current = *env;
	while (current)
	{
		content = (char *)current->content;
		if (!ft_strncmp(line, content, equal_index)
			&& (content[equal_index] == '=' || !content[equal_index]))
		{
			free(current->content);
			current->content = ft_strdup(line);
			if (!current->content)
				return (-1);
			return (1);
		}
		current = current->next;
	}
	return (1);
}

int	maybe_add_to_env(char *line, t_vars *v)
{
	if (!var_is_already_in_env(line, v->env_list))
		return (protected_addback(&v->env_list, line));
	if (!there_is_an_equal(line))
		return (1);
	else
		return (replace_the_var(&v->env_list, line));
}

void	ft_export(char **cmd, t_vars *vars)
{
	size_t	i;

	if (!cmd[1])
		print_env_export_list(vars->env_list);
	else
	{
		i = 0;
		while (cmd[++i])
		{
			if (!cmd[i][0])
				printfd(2, "🦑: export: `': not a valid identifier\n");
			else if (!is_correct_arg(cmd[i]))
				printfd(2, "🦑: export: `%s%s%s': not a valid identifier\n",
					PINK, cmd[i], RESET);
			else if (maybe_add_to_env(cmd[i], vars) == -1)
				return ;
		}
	}
}
