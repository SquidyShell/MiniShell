/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfd.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:33:49 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/10 21:28:28 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTFD_H
# define FT_PRINTFD_H
# include <unistd.h>

/* Colors */
# define BOLD "\033[1m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define RESET "\033[0m"

void	printfd(int fd, const char *s, ...);
int		ft_printf(const char *s, ...);
int		ft_printfd(int fd, const char *s, ...);
void	v_printf(const char *s, ...);
void	v_printfd(int fd, const char *s, ...);

int		ft_putunsigned_fd(unsigned int n, int fd);
int		ft_putaddr_fd(void *addr, int fd);
int		ft_puthexa_min_fd(unsigned long long hexa, int fd);
int		ft_puthexa_max_fd(unsigned long long hexa, int fd);

void	ft_print_s(const char **split);

/* Prints a bold red string ended with a return on the standard error */
void	perr(const char *s);

#endif