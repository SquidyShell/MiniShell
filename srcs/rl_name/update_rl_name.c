/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_rl_name.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 06:39:45 by cviegas          #+#    #+#             */
/*   Updated: 2024/03/20 15:13:33 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_new_name(char *pwd, bool pwd_is_root, t_vars *v)
{
	char	*pwd_to_print;

	p_free(v->readlinestring);
	if (pwd_is_root)
		pwd_to_print = strrchr(pwd, '/');
	else
		pwd_to_print = strrchr(pwd, '/') + 1;
	if (!g_exit_status)
		v->readlinestring = ft_strjoin3(GREENARROW BBLUE " ", pwd_to_print,
				RESET " " SQUIDYSHELL);
	else
		v->readlinestring = ft_strjoin3(REDARROW BBLUE " ", pwd_to_print,
				RESET " " SQUIDYSHELL);
}

void	update_rl_name(t_vars *v)
{
	bool	malloc_crampt;
	char	*pwd;

	malloc_crampt = 0;
	pwd = search_var_in_env(v, "PWD", &malloc_crampt);
	if (malloc_crampt)
		return (err_squid("Malloc", true), clean_vars(v), exit(FAILURE));
	if (!pwd)
		pwd = ft_strdup("");
	if (!pwd)
		return (clean_vars(v), exit(FAILURE));
	create_new_name(pwd, !pwd[1], v);
	p_free(pwd);
}
