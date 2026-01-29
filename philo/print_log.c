/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Elkan Choo <echoo@42mail.sutd.edu.sg>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 14:46:13 by Elkan Choo        #+#    #+#             */
/*   Updated: 2026/01/29 18:55:42 by Elkan Choo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// act 0: timestamp_in_ms X has taken a fork
// act 1: timestamp_in_ms X is eating
// act 2: timestamp_in_ms X is sleeping
// act 3: timestamp_in_ms X is thinking
// act 4: timestamp_in_ms X died

#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

void	print_log_2(int act, pthread_mutex_t print_mutex,
			long long unsigned int ms, int philo_num);

void	print_log(int act, pthread_mutex_t print_mutex,
			struct timeval time, int philo_num)
{
	long long unsigned int	ms;

	ms = time.tv_sec * 1000 + time.tv_usec / 1000;
	// TODO: if check death and time is after death, return
	if (act == 0)
	{
		pthread_mutex_lock(&print_mutex);
		printf("%llu %i has taken a fork\n", ms, philo_num);
		pthread_mutex_unlock(&print_mutex);
	}
	else if (act == 1)
	{
		pthread_mutex_lock(&print_mutex);
		printf("%llu %i is eating\n", ms, philo_num);
		pthread_mutex_unlock(&print_mutex);
	}
	else
		print_log_2(act, print_mutex, ms, philo_num);
}

void	print_log_2(int act, pthread_mutex_t print_mutex,
			long long unsigned int ms, int philo_num)
{
	if (act == 2)
	{
		pthread_mutex_lock(&print_mutex);
		printf("%llu %i is sleeping\n", ms, philo_num);
		pthread_mutex_unlock(&print_mutex);
	}
	else if (act == 3)
	{
		pthread_mutex_lock(&print_mutex);
		printf("%llu %i is thinking\n", ms, philo_num);
		pthread_mutex_unlock(&print_mutex);
	}
	else if (act == 4)
	{
		pthread_mutex_lock(&print_mutex);
		printf("%llu %i is thinking\n", ms, philo_num);
		pthread_mutex_unlock(&print_mutex);
	}
}
