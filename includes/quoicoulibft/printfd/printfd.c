/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printfd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:47:49 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/10 19:04:03 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/first_libft.h"
#include "ft_printfd.h"
#include "limits.h"
#include <stdarg.h>

static int	case_percent(const char *s, char *to_print, int i, va_list ap)
{
	i++;
	if (s[i] == '%')
		return (ft_putchar_fd('%', fd), 1);
	else if (s[i] == 'c')
		return (ft_putchar_fd(va_arg(ap, int), fd), 1);
	else if (s[i] == 's')
		return (ft_putstr_fd(va_arg(ap, char *), fd));
	else if (s[i] == 'p')
		return (ft_putaddr_fd(va_arg(ap, void *), fd));
	else if (s[i] == 'i' || s[i] == 'd')
		return (ft_putnbr_fd(va_arg(ap, int), fd));
	else if (s[i] == 'u')
		return (ft_putunsigned_fd(va_arg(ap, unsigned int), fd));
	else if (s[i] == 'x')
		return (ft_puthexa_min_fd(va_arg(ap, unsigned int), fd));
	else if (s[i] == 'X')
		return (ft_puthexa_max_fd(va_arg(ap, unsigned int), fd));
	return (0);
}

int	ft_printfd(int fd, const char *s, ...)
{
	va_list	ap;
	int		i;
	int		nb_printed;
	char	*to_print;
	t_list	*lst;

	if (!s || fd < 0)
		return (-1);
	to_print = NULL;
	nb_printed = 0;
	va_start(ap, s);
	i = -1;
	while (s[++i])
	{
		if (s[i] == '%')
			nb_printed += case_percent(s, to_print, i++, ap);
		else
			nb_printed++;
	}
	va_end(ap);
	return (nb_printed);
}
