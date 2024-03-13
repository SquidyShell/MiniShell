/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:05:13 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/13 17:55:57 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_list *env)
{
	t_list	*current;

	if (!env)
		return ;
	current = env;
	while (current)
	{
		if (current->content)
			printf("%s\n", (char *)current->content);
		current = current->next;
	}
}

static char	*find_min(char **env)
{
	size_t	i;
	char	*temp;

	if (!env)
		return (NULL);
	i = 0;
	temp = env[i];
	while (env[i])
	{
		if (ft_strcmp(env[i], temp) < 0)
			temp = env[i];
		i++;
	}
	return (temp);
}

static char	*smallest_above(char **env, char *previous)
{
	size_t	i;
	char	*temp;

	i = 0;
	temp = 0;
	while (env[i])
	{
		if (ft_strcmp(env[i], previous) > 0)
		{
			if (!temp)
				temp = env[i];
			else if (ft_strcmp(env[i], temp) < 0)
				temp = env[i];
		}
		i++;
	}
	return (temp);
}

// The "export" func without arg prints the env but sorting lines
// in ascending ascii order, with "declare -x" before each line
void	print_env_export(char **env)
{
	size_t	i;
	char	*temp_line;

	if (!env)
		return ;
	temp_line = find_min(env);
	i = 0;
	while (env[i])
	{
		if (temp_line[0] != '_' && temp_line[1] != '=')
			ft_printf("declare -x %s\n", temp_line);
		temp_line = smallest_above(env, temp_line);
		i++;
	}
}

bool	there_is_an_equal(char *line)
{
	while (*line)
	{
		if (*line == '=')
			return (1);
		line++;
	}
	return (0);
}
