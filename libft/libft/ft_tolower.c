/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 21:23:11 by cviegas           #+#    #+#             */
/*   Updated: 2023/11/07 21:25:07 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <unistd.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <ctype.h>

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c - 'A' + 'a');
	else
		return (c);
}

// int main(int ac, char **av)
// {	
// 	if (ac == 2)
// 	{
// 		printf("ft_toupper : %c\n", ft_tolower(*av[1]));
// 		printf("toupper    : %c\n", tolower(*av[1]));
// 	}
// }