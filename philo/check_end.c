/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elkan <elkan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 14:31:39 by Elkan Choo        #+#    #+#             */
/*   Updated: 2026/02/10 13:57:53 by elkan            ###   ########.fr       */
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
		pthread_mutex_lock(&info->end_time_mutex);
		if (!info->end_mcs)
			info->end_mcs = ((death_mcs - info->start_mcs) / 1000);
		pthread_mutex_unlock(&info->end_time_mutex);
		print_log(4, info, death_mcs - info->start_mcs, philo->philo_num);
		return (1);
	}
	return (0);
}
