/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min_max.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:31:59 by cviegas           #+#    #+#             */
/*   Updated: 2024/02/02 16:56:51 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MIN_MAX_H
# define FT_MIN_MAX_H
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int	ft_bmin(int a, int b);
int	ft_bmax(int a, int b);
int	ft_max(int number, ...);
int	ft_min(int number, ...);

#endif