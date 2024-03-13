/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printfd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:47:49 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/13 16:35:04 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/first_libft.h"
#include "ft_printfd.h"
#include "limits.h"
#include <stdarg.h>

static int	case_percent(const char *s, t_v2i ij, va_list ap, char buffer[])
{
	char	*temp;

	ij[0]++;
	if (s[ij[0]] == '%')
		if (ij[1] + 1 < BUFF_SIZE)
			return (buffer[ij[1]] = '%', 1);
		else
			return (1);
	else if (s[ij[0]] == 'c')
		if (ij[1] + 1 < BUFF_SIZE)
			return (buffer[ij[1]] = va_arg(ap, int), 1);
		else
			return (1);
	else if (s[ij[0]] == 's')
	{
		temp = va_arg(ap, char *);
		if (ij[1] + ft_strlen(temp) < BUFF_SIZE)
			return (ft_strlcpy(buffer + ij[1], temp, ft_strlen(temp) + 1));
		else
			return (ft_strlen(temp));
	}
	return (0);
}

void	printfd(int fd, const char *s, ...)
{
	va_list	ap;
	t_v2i	i;
	char	buffer[BUFF_SIZE + 1];

	ft_bzero(buffer, BUFF_SIZE + 1);
	if (!s || fd < 0)
		return ;
	i = (t_v2i){0, 0};
	va_start(ap, s);
	while (s[i[0]])
	{
		if (s[i[0]] == '%')
			i[1] += case_percent(s, (t_v2i){i[0]++, i[1]}, ap, buffer);
		else if (i[1] + 1 < BUFF_SIZE)
			buffer[i[1]++] = s[i[0]];
		if (i[1] >= BUFF_SIZE)
			break ;
		i[0]++;
	}
	va_end(ap);
	write(fd, buffer, ft_strlen(buffer));
}
