/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:26:48 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/15 11:26:35 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cd_free(void *a, void *b, void *c)
{
	free(a);
	free(b);
	free(c);
}

char	*ft_getcwd(void)
{
	char	*ret;
	char	*buff;
	size_t	size;

	ret = NULL;
	buff = NULL;
	size = 100;
	while (!ret)
	{
		ret = getcwd(buff, size);
		free(buff);
		size *= 2;
		if (errno == ERANGE)
			continue ;
	}
	return (ret);
}

static void	replace_pwd(t_vars *vars)
{
	bool	malloc_crampt;
	char	*old_pwd;
	char	*new_pwd;
	char	*new_old_pwd;

	old_pwd = search_var_in_env(vars, "PWD", &malloc_crampt);
	if (malloc_crampt)
		return ((void)perr("Malloc error, PWD not set"));
	new_pwd = ft_getcwd();
	if (!new_pwd)
		return (perror("getcwd"));
	new_pwd = ft_strjoin_free(ft_strdup("PWD="), new_pwd);
	if (!new_pwd || replace_the_var(&vars->env_list, new_pwd) == -1)
		return (cd_free(old_pwd, new_pwd, NULL),
			(void)perr("Malloc error,PWD not set"));
	new_old_pwd = ft_strjoin("OLDPWD=", old_pwd);
	if (!new_old_pwd || replace_the_var(&vars->env_list, new_old_pwd) == -1)
		(void)perr("Malloc error, OLDPWD not set");
	(free(old_pwd), free(new_pwd), free(new_old_pwd));
}

static void	case_home(t_vars *vars)
{
	char	*path;
	bool	malloc_crampt;

	path = search_var_in_env(vars, "HOME", &malloc_crampt);
	if (malloc_crampt)
		return (vars->exit_status = 1, perr("Malloc failed"));
	if (path == NULL)
		return (vars->exit_status = 1, perr("cd: HOME not set"));
	else if (chdir(path) == -1)
	{
		vars->exit_status = 1;
		perror("cd");
	}
	else
		replace_pwd(vars);
	free(path);
}

void	ft_cd(char **cmd, t_vars *vars)
{
	size_t	i;

	i = 0;
	while (cmd[i])
		i++;
	if (i > 2)
	{
		perr("cd: too many arguments");
		vars->exit_status = 1;
		return ;
	}
	if (i == 1)
		return (case_home(vars));
	else if (chdir(cmd[1]) == -1)
		(perror("cd"), vars->exit_status = 1);
	else
		replace_pwd(vars);
}
