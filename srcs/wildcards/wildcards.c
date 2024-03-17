/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 16:48:32 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/17 01:36:49 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_matching(const char *pattern, const char *filename)
{
	if (*pattern == 0)
		return (*filename == 0);
	if (*pattern == '*')
	{
		if (is_matching(pattern + 1, filename))
			return (1);
		return (*filename != 0 && is_matching(pattern, filename + 1));
	}
	if (*pattern == *filename)
		return (is_matching(pattern + 1, filename + 1));
	return (0);
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
		if ((file->d_type == 8 || file->d_type == 4) && *file->d_name != '.'
			&& ft_strcmp(file->d_name, ".."))
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
