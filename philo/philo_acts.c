/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_acts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elkan <elkan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 18:51:45 by elkan             #+#    #+#             */
/*   Updated: 2026/02/03 21:30:29 by elkan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <sys/time.h>
#include <stdio.h>

void	*philosopher_act(void *i);
int		update_times(t_info *info, t_philo *philo,
			long long unsigned int time_ate_mcs);

void	*philosopher_act(void *i)
{
	t_philo				philo;
	t_info				*info;
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
	while (info->run)
	{
		time_ate_ms = eating(info, &philo);
		print_log(1, info->print_mutex, time_ate_ms, philo.philo_num);
		if (update_times(info, &philo, time_ate_ms))
			return (NULL);
		if (wait_till(info, philo.sleep_mcs, philo.die_mcs))
			return (NULL);
		return_forks(info, &philo);
		print_log(2, info->print_mutex, philo.sleep_mcs, philo.philo_num);
		if (wait_till(info, philo.sleep_mcs, philo.die_mcs))
			return (NULL);
		print_log(3, info->print_mutex, philo.sleep_mcs, philo.philo_num);
		if (wait_till(info, philo.eat_mcs, philo.die_mcs))
			return (NULL);
	}
}

// If simulation has ended, initiates shutdown
int	update_times(t_info *info, t_philo *philo,
			long long unsigned int time_ate_mcs)
{
	if (!info->run)
		return (1);
	philo->die_mcs = time_ate_mcs + info->starve_mcs;
	philo->sleep_mcs = time_ate_mcs + info->eat_mcs;
	philo->wake_mcs = philo->sleep_mcs + info->sleep_mcs;
	philo->eat_mcs = time_ate_mcs + (2 + info->total_philo % 2) * info->eat_mcs;
	return (0);
}
