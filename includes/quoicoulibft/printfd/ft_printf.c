/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:16:18 by cviegas           #+#    #+#             */
/*   Updated: 2024/02/02 18:59:56 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/first_libft.h"
#include "ft_printfd.h"
#include "limits.h"
#include <stdarg.h>

static int	case_percent(const char *s, int i, va_list ap)
{
	i++;
	if (s[i] == '%')
		return (ft_putchar_fd('%', 1), 1);
	else if (s[i] == 'c')
		return (ft_putchar_fd(va_arg(ap, int), 1), 1);
	else if (s[i] == 's')
		return (ft_putstr_fd(va_arg(ap, char *), 1));
	else if (s[i] == 'p')
		return (ft_putaddr_fd(va_arg(ap, void *), 1));
	else if (s[i] == 'i' || s[i] == 'd')
		return (ft_putnbr_fd(va_arg(ap, int), 1));
	else if (s[i] == 'u')
		return (ft_putunsigned_fd(va_arg(ap, unsigned int), 1));
	else if (s[i] == 'x')
		return (ft_puthexa_min_fd(va_arg(ap, unsigned int), 1));
	else if (s[i] == 'X')
		return (ft_puthexa_max_fd(va_arg(ap, unsigned int), 1));
	return (0);
}

void	v_printf(const char *s, ...)
{
	va_list	ap;
	int		i;

	if (!s)
		return ;
	va_start(ap, s);
	i = 0;
	while (s[i])
	{
		if (s[i] == '%')
			case_percent(s, i++, ap);
		else
			ft_putchar_fd(s[i], 1);
		i++;
	}
	va_end(ap);
}

int	ft_printf(const char *s, ...)
{
	va_list	ap;
	int		i;
	int		nb_printed;

	if (!s)
		return (-1);
	va_start(ap, s);
	nb_printed = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '%')
			nb_printed += case_percent(s, i++, ap);
		else
		{
			ft_putchar_fd(s[i], 1);
			nb_printed++;
		}
		i++;
	}
	va_end(ap);
	return (nb_printed);
}

// Prints a char **
void	ft_print_s(const char **split)
{
	size_t	i;

	i = 0;
	while (split[i])
	{
		ft_printf("%s", split[i++]);
		if (split[i])
			ft_printf(" ");
		i++;
	}
}
