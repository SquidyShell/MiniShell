/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_tlist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:31:25 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/13 12:31:49 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(char **env)
{
	size_t	i;

	if (!env)
		return ;
	i = 0;
	while (env[i])
		ft_printf("%s\n", env[i++]);
}

char	*find_min(char **env)
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

char	*smallest_above(char **env, char *previous)
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
