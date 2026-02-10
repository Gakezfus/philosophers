/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_acts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elkan <elkan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 18:51:45 by elkan             #+#    #+#             */
/*   Updated: 2026/02/10 14:01:06 by elkan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <sys/time.h>
#include <stdio.h>

void	*philosopher_act(void *i);
int		update_times(t_info *info, t_philo *philo,
			long long unsigned int time_ate_mcs);

// TODO: Make Norm compliant
void	*philosopher_act(void *i)
{
	t_philo				philo;
	t_info				*info;
	unsigned long long	time_ate_ms;

	info = (t_info *)i;
	philo_setup(info, &philo);
	while (1)
	{
		if (wait_till(info, &philo, philo.eat_mcs, philo.die_mcs))
			return (NULL);
		time_ate_ms = eating(info, &philo);
		if (!time_ate_ms)
			return (NULL);
		print_log(1, info, time_ate_ms - info->start_mcs, philo.philo_num);
		manage_eat_limit(info, &philo);
		if (update_times(info, &philo, time_ate_ms))
			return (NULL);
		if (wait_till(info, &philo, philo.sleep_mcs, philo.die_mcs))
			return (NULL);
		return_forks(info, &philo);
		print_log(2, info, philo.sleep_mcs - info->start_mcs, philo.philo_num);
		if (wait_till(info, &philo, philo.sleep_mcs, philo.die_mcs))
			return (NULL);
		print_log(3, info, philo.wake_mcs - info->start_mcs, philo.philo_num);
		pthread_mutex_lock(&info->r_mutex);
		if (!info->run)
			return (pthread_mutex_unlock(&info->r_mutex), NULL);
		pthread_mutex_unlock(&info->r_mutex);
	}
	return (NULL);
}

// If simulation has ended, initiates shutdown
int	update_times(t_info *info, t_philo *philo,
			long long unsigned int time_ate_mcs)
{
	pthread_mutex_lock(&info->r_mutex);
	if (!info->run)
		return (pthread_mutex_unlock(&info->r_mutex), 1);
	pthread_mutex_unlock(&info->r_mutex);
	philo->die_mcs = time_ate_mcs + info->starve_mcs;
	philo->sleep_mcs = time_ate_mcs + info->eat_mcs;
	philo->wake_mcs = philo->sleep_mcs + info->sleep_mcs;
	philo->eat_mcs = time_ate_mcs + (2 + info->total_philo % 2) * info->eat_mcs;
	return (0);
}
