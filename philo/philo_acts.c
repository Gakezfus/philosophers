/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_acts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Elkan Choo <echoo@42mail.sutd.edu.sg>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 18:51:45 by elkan             #+#    #+#             */
/*   Updated: 2026/01/29 18:55:35 by Elkan Choo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <sys/time.h>
#include <stdio.h>

void	*philosopher_act(void *i);
void	update_times(info, philo, time);

void	*philosopher_act(void *i)
{
	t_philo			philo;
	t_info			*info;

	info = (t_info *)i;
	pthread_mutex_lock(&(info->p_num_mutex));
	philo.philo_num = info->philo_num;
	info->philo_num++;
	pthread_mutex_unlock(&(info->p_num_mutex));
	philo_setup(info, &philo);
	pthread_mutex_lock(&info->r_mutex);
	pthread_mutex_unlock(&info->r_mutex);
	eating(info, &philo);
	wait_till(philo.sleep_time_mcs, philo.die_time_mcs);
	return_forks(info, &philo);
	// try to sleep
	// try to think
	return (NULL);
}

void	update_times(t_info *info, t_philo *philo, struct timeval time_ate)
{
	long long unsigned int time_ate_ms;

	time_ate_ms = time_ate.tv_sec * 1000000 + time_ate.tv_usec;
	philo->die_time_mcs = time_ate_ms + info->starve_mcs;
	philo->sleep_time_mcs = time_ate_ms + info->eat_mcs;
	philo->wake_time_mcs = philo->sleep_time_mcs + info->sleep_mcs;
	philo->eat_time_mcs = time_ate_ms + (2 + info->total_philo % 2) * info->eat_mcs;
}
