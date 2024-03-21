/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:22:52 by cviegas           #+#    #+#             */
/*   Updated: 2023/11/07 20:35:15 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <unistd.h>
// #include <stdio.h>
// #include <stdlib.h>

int	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9')
		|| (c >= 'a' && c <= 'z' )
		|| (c >= 'A' && c <= 'Z' ))
		return (1);
	else
		return (0);
}

// int	main(int ac, char **av)
// {	
// 	printf("%d\n", ft_isalnum('a'));
// 	if (ac == 2)
// 		printf("%d\n", ft_isalnum(av[1][0]));
// }
