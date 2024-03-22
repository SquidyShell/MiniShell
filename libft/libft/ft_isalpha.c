/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:56:03 by cviegas           #+#    #+#             */
/*   Updated: 2023/11/10 17:14:38 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <unistd.h>
// #include <stdio.h>
// #include <stdlib.h>

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

// int main(int ac, char **av)
// {	
// 	printf("%d", ft_isalpha('a'));
// 	if (ac == 2)
// 		printf("%d", ft_isalpha(atoi(av[1])));
// }