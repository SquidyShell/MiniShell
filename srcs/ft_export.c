/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:28:24 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/12 17:29:02 by cviegas          ###   ########.fr       */
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

// // Do same but with a t_list instead of a char **
// void	print_env_export_list(t_list *env)
// {
// 	t_list	*temp;
// 	t_list	*min;

// 	if (!env)
// 		return ;
// 	temp = env;
// 	while (temp)
// 	{
// 		min = find_min_list(env);
// 		if (min->content[0] != '_' && min->content[1] != '=')
// 			ft_printf("declare -x %s\n", min->content);
// 		temp = smallest_above_list(env, min);
// 	}
// }

void	ft_export(char **cmd, t_vars *vars)
{
	if (!cmd[1])
		print_env_export(vars->env);
}
