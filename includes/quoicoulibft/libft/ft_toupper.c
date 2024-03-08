/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 21:14:38 by cviegas           #+#    #+#             */
/*   Updated: 2023/11/07 21:25:23 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <unistd.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <ctype.h>

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 'a' + 'A');
	else
		return (c);
}

// int main(int ac, char **av)
// {	
// 	if (ac == 2)
// 	{
// 		printf("ft_toupper : %c\n", ft_toupper(*av[1]));
// 		printf("toupper    : %c\n", toupper(*av[1]));
// 	}
// }