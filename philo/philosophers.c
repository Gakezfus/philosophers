/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elkan <elkan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 18:51:45 by elkan             #+#    #+#             */
/*   Updated: 2026/01/28 20:13:48 by elkan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <sys/time.h>
#include <stdio.h>

void	*philosopher_act(void *i)
{
	struct timeval	time;
	t_philo			philo;
	t_info			*info;

	info = (t_info *)i;
	pthread_mutex_lock(&(info->p_num_mutex));
	philo.philo_num = info->philo_num;
	info->philo_num++;
	pthread_mutex_unlock(&(info->p_num_mutex));
	philo.dom_hand = philo.philo_num % 2;
	pthread_mutex_lock(&info->r_mutex);
	pthread_mutex_unlock(&info->r_mutex);
	
	// try to eat
	gettimeofday(&time, NULL);
	// print log that the philosopher has eaten
	philo.die_time_s = time.tv_sec + info->starve_s
		+ (time.tv_usec + info->starve_mcs) / 1000ll;
	philo.die_time_mcs = (time.tv_usec + info->starve_mcs) % 1000000LL;
	// try to sleep
	philo.sleep_time_s = time.tv_sec + info->eat_s
		+ (time.tv_usec + info->sleep_mcs) / 1000000LL;
	philo.sleep_time_mcs = (time.tv_usec + info->eat_mcs) % 1000000LL;
	// try to think
	philo.think_time_s = philo.sleep_time_s + info->eat_s
		+ (time.tv_usec + philo.think_time_mcs) / 1000000LL;
	philo.think_time_mcs = (philo.sleep_time_mcs + philo.think_time_s)
		% 1000000LL;
	return (NULL);
}
