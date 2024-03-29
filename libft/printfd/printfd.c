/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printfd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:47:49 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/21 13:13:18 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/first_libft.h"
#include "ft_printfd.h"
#include "limits.h"
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>

static int	case_percent(const char *s, t_v2i *ij, va_list ap, char buffer[])
{
	char	*temp;
	size_t	tempnb;

	(*ij)[0]++;
	if (s[(*ij)[0]] == '%')
		return (buffer[(*ij)[1]] = '%', 1);
	if (s[(*ij)[0]] == 'c')
		return (buffer[(*ij)[1]] = va_arg(ap, int), 1);
	if (s[(*ij)[0]] == 's')
	{
		temp = va_arg(ap, char *);
		if (!temp[0])
			return (0);
		else
			return (ft_strlcpy(buffer + (*ij)[1], temp, ft_strlen(temp) + 1));
	}
	if (s[(*ij)[0]] == 'z' && s[(*ij)[0] + 1] == 'u')
	{
		tempnb = va_arg(ap, unsigned int);
		(*ij)[0]++;
		return (fill_in_sizet(buffer + (*ij)[1], tempnb),
			count_print_sizet(tempnb));
	}
	return (0);
}

static int	count_percent(const char *s, t_v2i *ij, va_list ap)
{
	char	*temp;

	(*ij)[0]++;
	if (s[(*ij)[0]] == '%')
		return (1);
	if (s[(*ij)[0]] == 'c')
		return (1);
	if (s[(*ij)[0]] == 's')
	{
		temp = va_arg(ap, char *);
		if (!temp[0])
			return (0);
		else
			return (ft_strlen(temp) + 1);
	}
	if (s[(*ij)[0]] == 'z' && s[(*ij)[0] + 1] == 'u')
	{
		(*ij)[0]++;
		return (count_print_sizet(va_arg(ap, size_t)));
	}
	return (1);
}

void	fill_in_buffer(char *buffer, const char *s, va_list ap)
{
	t_v2i	i;

	i = (t_v2i){0, 0};
	while (s[i[0]])
	{
		if (s[i[0]] == '%')
			i[1] += case_percent(s, &i, ap, buffer);
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
			i[1] += count_percent(s, &i, ap);
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
