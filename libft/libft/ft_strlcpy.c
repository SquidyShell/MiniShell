/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:42:12 by cviegas           #+#    #+#             */
/*   Updated: 2023/11/08 21:34:50 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// size_t	strlcpy(char *dst, const char *src, size_t size);

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size != 0)
	{
		while (src[i] && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = 0;
	}
	while (src[i])
		i++;
	return (i);
}

// int	main(void)
// {
// 	// strlcpy
// 	printf("\n---- strlcpy ---\n");
// 	char src_real2[] = "12";
//     char dest_real2[19];
//     char dest_test2[19];
//     int src_real2_s;
//     int src_test2_s;
//     src_test2_s = ft_strlcpy(dest_test2, src_real2, 5);
//     src_real2_s = strlcpy(dest_real2, src_real2, 5);
//     printf("Real : Copied '%s' into '%s', length %d\n", src_real2,
// dest_real2, src_real2_s);
//     printf("Test : Copied '%s' into '%s', length %d\n", src_real2,
// dest_test2, src_test2_s);

// }

// int	main(int argc, char **argv)
// {
// 	if (argc == 4)
// 	{
// 		char *destination = argv[1];
// 		const char *source = argv[2];
// 		size_t size_of_destination = (size_t)atoi(argv[3]);
// 		char *destination2 = argv[1];
// 		const char *source2 = argv[2];
// 		size_t size_of_destination2 = (size_t)atoi(argv[3]);
// 		size_t result = strlcpy(destination, source, size_of_destination);
// 		printf("Copied string: %s\n", destination);
// 		printf("Return value: %zu\n", result);

// 		size_t result2 = ft_strlcpy(destination2, source2,
				// size_of_destination2);
// 		printf("Copied string: %s\n", destination2);
// 		printf("Return value: %zu\n", result2);
// 	}
// 	else
// 	{
// 		printf("Usage: %s <destination> <source> <size>\n", argv[0]);
// 	}

// 	return (0);
// }