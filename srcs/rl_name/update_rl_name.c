/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_rl_name.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 06:39:45 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/22 01:49:25 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rm_suffix(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '.' || s[i] == '\n' || is_whitespace(s[i]))
		{
			return ((void)(s[i] = 0));
		}
		if (i > 10)
		{
			s[i] = 0;
			s[i - 1] = '.';
			s[i - 2] = '.';
			return ;
		}
		i++;
	}
}

void	add_arrow(char *s)
{
	size_t	i;

	i = len(s) - 1;
	while (i > 0)
	{
		s[i + 2] = s[i];
		i--;
	}
	s[i + 2] = s[i];
	s[1] = '~';
	s[0] = ' ';
}

void	join_line(t_vars *v, char *to_print, char *git_b, bool print_gitname)
{
	if (!g_exit_status)
	{
		if (!print_gitname)
			v->readlinestring = ft_strjoin3(GREENARROW " " SQUIDYSHELL BBLUE,
					to_print, RESET " ");
		else
			v->readlinestring = ft_strjoin_4(GREENARROW " " SQUIDYSHELL BLUE
					"git:(" RESET RRED, to_print, git_b, BLUE ") " RESET);
	}
	else
	{
		if (!print_gitname)
				v->readlinestring = ft_strjoin3(REDARROW " " SQUIDYSHELL BBLUE,
					to_print, RESET " ");
		else
				v->readlinestring = ft_strjoin_4(REDARROW " " SQUIDYSHELL BLUE
					"git:(" RESET RRED, to_print, git_b, BLUE ") " RESET);
	}
}

void	create_new_name(char *to_print, t_vars *v)
{
	char	git_r[1024];
	char	git_b[1024];
	int		print_gitname;
	int		end[2];

	(ft_bzero(git_b, 1024), ft_bzero(git_r, 1024));
	print_gitname = get_git_r(end, git_r, v);
	if (print_gitname == -1)
		return (p_free(v->pwd), clean_vars(v), exit(FAILURE));
	if (print_gitname)
	{
		to_print = ft_strrchr(git_r, '/') + 1;
		print_gitname = get_git_b(end, git_b, v);
		if (print_gitname == -1)
			return (p_free(v->pwd), clean_vars(v), exit(FAILURE));
		(rm_suffix(git_b), add_arrow(git_b), rm_suffix(to_print));
	}
	join_line(v, to_print, git_b, print_gitname);
	if (!v->readlinestring)
		return (p_free(v->pwd), clean_vars(v), exit(FAILURE));
}

/*Omz behavior for prompt name when cwd is null*/
void	update_rl_name(t_vars *v)
{
	char	*to_print;

	v->pwd = NULL;
	v->pwd = ft_getcwd();
	if (!v->pwd)
		v->pwd = ft_strdup(".");
	if (v->pwd)
	{
		free(v->readlinestring);
		if (!ft_strcmp(v->pwd, "/") || !ft_strcmp(".", v->pwd))
			to_print = v->pwd;
		else
			to_print = ft_strrchr(v->pwd, '/') + 1;
		if (v->gigit)
			create_new_name(to_print, v);
		else
		{
			join_line(v, to_print, NULL, 0);
			if (!v->readlinestring)
				return (p_free(v->pwd), clean_vars(v), exit(FAILURE));
		}
		p_free(v->pwd);
	}
}
