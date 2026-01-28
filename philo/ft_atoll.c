/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Elkan Choo <echoo@42mail.sutd.edu.sg>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 10:55:58 by Elkan Choo        #+#    #+#             */
/*   Updated: 2025/12/24 10:56:01 by Elkan Choo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <limits.h>

// Numbers are processed as negative by default. May be slightly confusing.
// This atoll has been specially customised to return 0 if overor underflow is
// detected. This is fine since 0 is not an acceptable input in this program.
long long int	ft_atoll(const char *str)
{
	int				negative;
	int				index;
	long long int	to_return;

	negative = -1;
	index = 0;
	while (str[index] == ' ' || ('\t' <= str[index] && str[index] <= '\r'))
		index++;
	if (str[index] == '-' || str[index] == '+')
	{
		if (str[index++] == '-')
			negative = -negative;
	}
	to_return = 0;
	while (('0' <= str[index] && str[index] <= '9'))
	{
		if (negative < 0 && to_return - str[index] - '0' > LLONG_MAX / 10)
			return (0);
		if (negative > 0 && to_return - str[index] - '0' < LLONG_MIN / 10)
			return (0);
		to_return *= 10;
		to_return -= str[index++] - '0';
	}
	to_return *= negative;
	return (to_return);
}
