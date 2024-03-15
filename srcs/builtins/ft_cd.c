/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:26:48 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/15 11:12:32 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cd_free(void *a, void *b, void *c)
{
	free(a);
	free(b);
	free(c);
}

static void	replace_pwd(t_vars *vars)
{
	bool	malloc_crampt;
	char	*old_pwd;
	char	*new_pwd;
	char	*new_old_pwd;

	old_pwd = search_var_in_env(vars, "PWD", &malloc_crampt);
	if (malloc_crampt)
		return ((void)perr("Malloc error, OLDPWD will not be set"));
	if (!old_pwd)
		old_pwd = ft_strdup("");
	new_pwd = ft_getcwd();
	if (!new_pwd)
		(printfd(2, "cd: " GETCWD_ERROR " %s\n", strerror(errno)),
			new_pwd = ft_strjoin_free(ft_strdup("PWD="), ft_strjoin3(old_pwd,
					"/", vars->cmd.args[1])));
	else
		new_pwd = ft_strjoin_free(ft_strdup("PWD="), new_pwd);
	if (!new_pwd || maybe_add_to_env(new_pwd, vars) == -1)
		return (cd_free(old_pwd, new_pwd, NULL),
			(void)perr("Malloc error,PWD will not be set"));
	new_old_pwd = ft_strjoin("OLDPWD=", old_pwd);
	if (!new_old_pwd || maybe_add_to_env(new_old_pwd, vars) == -1)
		(void)perr("Malloc error, OLDPWD will not be set");
	(free(old_pwd), free(new_pwd), free(new_old_pwd));
}

static void	case_home(t_vars *vars)
{
	char	*path;
	bool	malloc_crampt;

	path = search_var_in_env(vars, "HOME", &malloc_crampt);
	if (malloc_crampt)
		return (vars->exit_status = 1, perr("command failed: malloc error"));
	if (path == NULL)
		return (vars->exit_status = 1, perr("cd: HOME not set"));
	else if (chdir(path) == -1)
	{
		vars->exit_status = 1;
		printfd(2, "cd: %s: %s\n", path, strerror(errno));
	}
	else
		replace_pwd(vars);
	free(path);
}

static void	case_oldpwd(t_vars *vars)
{
	char	*path;
	bool	malloc_crampt;

	path = search_var_in_env(vars, "OLDPWD", &malloc_crampt);
	if (malloc_crampt)
		return (vars->exit_status = 1, perr("command failed: malloc error"));
	if (path == NULL)
		return (vars->exit_status = 1, perr("cd: OLDPWD not set"));
	else if (chdir(path) == -1)
	{
		vars->exit_status = 1;
		printfd(2, "cd: %s: %s\n", path, strerror(errno));
	}
	else
		replace_pwd(vars);
	free(path);
}

/*Behavior of bash 5.1.16 and not bash posix,
	bash will first use chdir and then use getcwd to change the PWD and OLDPWD,
		while bash --posix will check first and return if getcwd is null
			(e.g. "cd .." when the parent was removed)*/
void	ft_cd(char **cmd, t_vars *vars)
{
	char	*path;

	path = NULL;
	if (cmd[2])
	{
		perr("cd: too many arguments");
		vars->exit_status = 1;
		return ;
	}
	if (!cmd[1])
		return (case_home(vars));
	else if (ft_strcmp(cmd[1], "-") == 0)
		return (case_oldpwd(vars));
	else if (chdir(cmd[1]) == -1)
		(printfd(2, "cd: %s: %s\n", cmd[1], strerror(errno)),
			vars->exit_status = 1);
	else
		replace_pwd(vars);
}
