/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bits.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Elkan Choo <echoo@42mail.sutd.edu.sg>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 16:43:55 by Elkan Choo        #+#    #+#             */
/*   Updated: 2026/02/06 16:43:58 by Elkan Choo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdint.h>
// #include <stdlib.h>
// #include <stdio.h>

// int	main(int argc, char *argv[])
// {
// 	int			number;
// 	int			index;
// 	uint64_t	*bit_array;

// 	if (argc != 2)
// 	{
// 		printf("Include the number!\n");
// 		return (1);
// 	}
// 	number = atoi(argv[1]);
// 	bit_array = calloc((number / 64 + 1), sizeof(uint64_t));
// 	for (int i = 0; i <= number; i++)
// 	{
// 		if (i % 2 == 0)
// 		{
// 			bit_array[i / 64] |= 1ULL << i % 64;
// 		}
// 	}
// 	for (int i = 0; i <= number / 64; i++)
// 	{
// 		while (bit_array[i] != 0)
// 		{
// 			index = __builtin_ctzll(bit_array[i]);
// 			printf(": %i\n", i * 64 + index);
// 			bit_array[i] &= bit_array[i] - 1;
// 		}
// 	}
// 	free(bit_array);
// }
