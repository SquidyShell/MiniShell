/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:33:53 by cviegas           #+#    #+#             */
/*   Updated: 2024/02/06 19:29:59 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line_aux(int fd, char *buff, char *line, t_list *stash)
{
	int	red;

	red = read(fd, buff, BUFFER_SIZE);
	buff[red] = 0;
	while (red && !return_in_buff(buff))
	{
		ft_lstadd_back(&stash, ft_lstnew(buff_to_char(buff)));
		red = read(fd, buff, BUFFER_SIZE);
		buff[red] = 0;
	}
	if (stash || return_in_buff(buff))
	{
		ft_lstadd_back(&stash, ft_lstnew(buff_to_char(buff)));
		line = stash_to_line(stash);
		ft_strlcpy(buff, buff + return_in_buff(buff), BUFFER_SIZE + 1);
		ft_lstclear(&stash, free);
		return (line);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1];
	char		*line;
	t_list		*stash;

	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, &line, 0) < 0)
		return (NULL);
	stash = NULL;
	line = NULL;
	if (return_in_buff(buff))
	{
		line = buff_to_char(buff);
		ft_strlcpy(buff, buff + return_in_buff(buff), BUFFER_SIZE + 1);
		return (line);
	}
	if (buff[0])
		ft_lstadd_back(&stash, ft_lstnew(buff_to_char(buff)));
	return (get_next_line_aux(fd, buff, line, stash));
}

// Cree une string a partir du buffer, en copiant chaque caractere
// jusqu'au /n compris s'il y en a un, tout le buffer sinon.
char	*buff_to_char(char buff[])
{
	char	*string_to_lst;
	int		i;
	int		size;

	size = 0;
	while (buff[size] && buff[size] != '\n')
		size++;
	string_to_lst = malloc(sizeof(char) * (size + 2));
	if (!string_to_lst)
		return (free(buff), NULL);
	i = 0;
	while (i <= size && buff[i])
	{
		string_to_lst[i] = buff[i];
		i++;
	}
	string_to_lst[i] = 0;
	return (string_to_lst);
}

// Renvoie 0 sil ny en a pas, sinon l'emplacement + 1 du premier /n.
int	return_in_buff(char buff[])
{
	int	i;

	i = 1;
	while (buff[i - 1])
	{
		if (buff[i - 1] == '\n')
			return (i);
		i++;
	}
	return (0);
}

// int	main(int ac, char **av)
// {
// 	int		fd;
// 	char	*line;
// 	int		i;

// 	(void)ac;
// 	fd = open(av[1], O_RDONLY);
// 	printf("fd : %d\n", fd);
// 	i = 0;
// 	while ("squidgame")
// 	{
// 		line = get_next_line(fd);
// 		printf("%d : %s", i, line);
// 		if (!line)
// 			break ;
// 		free(line);
// 		i++;
// 	}
// }
