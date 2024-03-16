/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 16:48:32 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/16 18:15:13 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_matching(char *s, char *file)
{
	size_t	i;
	char	to_match;

	i = 0;
	while (s[i] && file[i])
	{
		if (s[i] == file[i])
			i++;
		else if (s[i] == '*')
		{
			to_match = s[i + 1];
			if (!to_match)
				return (true);
			while (file[i] && file[i] != to_match)
				i++;
		}
		else if (s[i] != file[i])
			return (false);
	}
	return (true);
}

int	main(int argc, char *argv[])
{
	DIR				*dir;
	struct dirent	*file;
	bool			z;
	size_t			i;

	dir = opendir(".");
	if (!dir)
		printf("rip\n");
	i = 0;
	z = argc == 2;
	if (!z)
		dprintf(2, "enter a wildcard pattern to test\n");
	while (dir && z)
	{
		file = readdir(dir);
		if (!file)
			break ;
		if (file->d_type == 8)
		{
			if (is_matching(argv[1], file->d_name))
				printf(GREEN "%s matched with %s\n" RESET, file->d_name,
					argv[1]);
			else
				printf(RED "%s did not match\n" RESET, file->d_name);
		}
	}
	if (dir)
		closedir(dir);
	return (0);
}
