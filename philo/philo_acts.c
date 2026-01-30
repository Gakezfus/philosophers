/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_acts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Elkan Choo <echoo@42mail.sutd.edu.sg>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 18:51:45 by elkan             #+#    #+#             */
/*   Updated: 2026/01/30 19:11:50 by Elkan Choo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <sys/time.h>
#include <stdio.h>

void	*philosopher_act(void *i);
void	update_times(t_info *info, t_philo *philo, struct timeval time_ate);

void	*philosopher_act(void *i)
{
	t_philo				philo;
	t_info				*info;
	struct timeval		time_ate;
	unsigned long long	time_ate_ms;

	info = (t_info *)i;
	philo.eat_limit = 0;
	pthread_mutex_lock(&(info->p_num_mutex));
	philo.philo_num = info->philo_num;
	info->philo_num++;
	pthread_mutex_unlock(&(info->p_num_mutex));
	philo_setup(info, &philo);
	pthread_mutex_lock(&info->r_mutex);
	pthread_mutex_unlock(&info->r_mutex);
	time_ate = eating(info, &philo);
	time_ate_ms = time_ate.tv_sec * 1000000 + time_ate.tv_usec;
	if (print_log(1, info->print_mutex, time_ate_ms, philo.philo_num)
		|| wait_till(info, philo.sleep_mcs, philo.die_mcs))
	// initiate shutdown
		return (NULL);
	return_forks(info, &philo);
	// try to sleep
	// try to think
	return (NULL);
}

void	update_times(t_info *info, t_philo *philo, struct timeval time_ate)
{
	long long unsigned int	time_ate_mcs;

	time_ate_mcs = time_ate.tv_sec * 1000000 + time_ate.tv_usec;
	philo->die_mcs = time_ate_mcs + info->starve_mcs;
	philo->sleep_mcs = time_ate_mcs + info->eat_mcs;
	philo->wake_mcs = philo->sleep_mcs + info->sleep_mcs;
	philo->eat_mcs = time_ate_mcs + (2 + info->total_philo % 2) * info->eat_mcs;
}
