/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Elkan Choo <echoo@42mail.sutd.edu.sg>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 14:31:39 by Elkan Choo        #+#    #+#             */
/*   Updated: 2026/02/06 18:24:12 by Elkan Choo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <stdio.h>

int	check_death(t_info *info, t_philo *philo, unsigned long long now_mcs,
		unsigned long long death_mcs);

// This function checks if the philosopher calling this function has died.
int	check_death(t_info *info, t_philo *philo, unsigned long long now_mcs,
		unsigned long long death_mcs)
{
	if (now_mcs >= death_mcs)
	{
		int	fork_1 = philo->fork_i[0];
		int	fork_2 = philo->fork_i[1];

		printf("%i: Time to eat: %llu\nForks: %lli, %lli\n", philo->philo_num, (philo->eat_mcs - info->start_mcs) / 1000, info->forks[fork_1 / 64] & 1ULL << (fork_1 % 64), info->forks[fork_2 / 64] & 1ULL << (fork_2 % 64));
		print_log(4, info, death_mcs - info->start_mcs, philo->philo_num);
		info->end_mcs = death_mcs;
		return (1);
	}
	return (0);
}
