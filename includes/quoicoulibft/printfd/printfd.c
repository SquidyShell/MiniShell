/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printfd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:47:49 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/13 18:27:12 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/first_libft.h"
#include "ft_printfd.h"
#include "limits.h"
#include <stdarg.h>
#include <stdlib.h>

static int	case_percent(const char *s, t_v2i ij, va_list ap, char buffer[])
{
	char	*temp;

	ij[0]++;
	if (s[ij[0]] == '%')
		return (buffer[ij[1]] = '%', 1);
	else if (s[ij[0]] == 'c')
		return (buffer[ij[1]] = va_arg(ap, int), 1);
	else if (s[ij[0]] == 's')
	{
		temp = va_arg(ap, char *);
		return (ft_strlcpy(buffer + ij[1], temp, ft_strlen(temp) + 1));
	}
	return (0);
}

static int	count_percent(const char *s, t_v2i ij, va_list ap)
{
	char	*temp;

	ij[0]++;
	if (s[ij[0]] == '%')
		return (1);
	else if (s[ij[0]] == 'c')
		return (1);
	else if (s[ij[0]] == 's')
	{
		temp = va_arg(ap, char *);
		return (ft_strlen(temp) + 1);
	}
	return (0);
}

void	fill_in_buffer(char *buffer, const char *s, va_list ap)
{
	t_v2i	i;

	i = (t_v2i){0, 0};
	while (s[i[0]])
	{
		if (s[i[0]] == '%')
			i[1] += case_percent(s, (t_v2i){i[0]++, i[1]}, ap, buffer);
		else
			buffer[i[1]++] = s[i[0]];
		i[0]++;
	}
	buffer[i[1]] = 0;
}

void	printfd(int fd, const char *s, ...)
{
	va_list	ap;
	t_v2i	i;
	char	*buffer;

	if (!s || fd < 0)
		return ;
	i = (t_v2i){0, 0};
	va_start(ap, s);
	while (s[i[0]])
	{
		if (s[i[0]] == '%')
			i[1] += count_percent(s, (t_v2i){i[0]++, i[1]}, ap);
		else
			i[1]++;
		i[0]++;
	}
	va_end(ap);
	buffer = malloc(sizeof(char) * (i[1] + 1));
	if (!buffer)
		return ;
	va_start(ap, s);
	fill_in_buffer(buffer, s, ap);
	va_end(ap);
	write(fd, buffer, ft_strlen(buffer));
	free(buffer);
}
