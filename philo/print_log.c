/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Elkan Choo <echoo@42mail.sutd.edu.sg>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 14:46:13 by Elkan Choo        #+#    #+#             */
/*   Updated: 2026/02/05 14:42:55 by Elkan Choo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// act 0: timestamp_in_mcs X has taken a fork
// act 1: timestamp_in_mcs X is eating
// act 2: timestamp_in_mcs X is sleeping
// act 3: timestamp_in_mcs X is thinking
// act 4: timestamp_in_mcs X died

#include "philo.h"

#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

void	print_log_2(int act, t_info *info,
			unsigned long long now_ms, int philo_num);

int	print_log(int act, t_info *info,
			unsigned long long now_ms, int philo_num)
{
	if (!info->run && now_ms >= info->end_mcs && act != 4)
		return (1);
	if (act == 0)
	{
		pthread_mutex_lock(&info->print_mutex);
		printf("%llu %i has taken a fork\n", now_ms / 1000, philo_num);
		pthread_mutex_unlock(&info->print_mutex);
	}
	else if (act == 1)
	{
		pthread_mutex_lock(&info->print_mutex);
		printf("%llu %i is eating\n", now_ms / 1000, philo_num);
		pthread_mutex_unlock(&info->print_mutex);
	}
	else
	{
		print_log_2(act, info, now_ms, philo_num);
	}
	return (0);
}

// Note: For death, now_ms given will be death_mcs, so now_ms is equivalent
// to 
void	print_log_2(int act, t_info *info,
			unsigned long long now_ms, int philo_num)
{
	if (act == 2)
	{
		pthread_mutex_lock(&info->print_mutex);
		printf("%llu %i is sleeping\n", now_ms / 1000, philo_num);
		pthread_mutex_unlock(&info->print_mutex);
	}
	else if (act == 3)
	{
		pthread_mutex_lock(&info->print_mutex);
		printf("%llu %i is thinking\n", now_ms / 1000, philo_num);
		pthread_mutex_unlock(&info->print_mutex);
	}
	else if (act == 4)
	{
		info->run = 0;
		pthread_mutex_lock(&info->print_mutex);
		printf("%llu %i died\n", now_ms / 1000, philo_num);
		pthread_mutex_unlock(&info->print_mutex);
	}
}
