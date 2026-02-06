/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Elkan Choo <echoo@42mail.sutd.edu.sg>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 21:34:19 by elkan             #+#    #+#             */
/*   Updated: 2026/02/06 18:00:34 by Elkan Choo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

unsigned long long	eating(t_info *info, t_philo *philo);
void				return_forks(t_info *info, t_philo *philo);
void				manage_eat_limit(t_info *info, t_philo *philo);

void				grab_fork(t_info *info, t_philo *philo, int fork);

// For dom hand, 0 is right, 1 is left, assuming clockwise seating
unsigned long long	eating(t_info *info, t_philo *philo)
{
	int					fork_1;
	int					fork_2;
	struct timeval		time;
	unsigned long long	time_mcs;

	fork_1 = philo->fork_i[0];
	fork_2 = philo->fork_i[1];
	gettimeofday(&time, NULL);
	time_mcs = time.tv_sec * 1000000 + time.tv_usec;
	while (philo->forks_held != 2 && !check_death(info, philo,
			time_mcs, philo->die_mcs))
	{
		if (philo->forks_held == 0)
			grab_fork(info, philo, fork_1);
		if (philo->forks_held == 1)
			grab_fork(info, philo, fork_2);
		if (philo->forks_held != 2)
			usleep(1000);
		gettimeofday(&time, NULL);
		time_mcs = time.tv_sec * 1000000 + time.tv_usec;
	}
	// manage_eat_limit(info, philo);
	philo->eat_limit++;
	if (info->eat_limit && philo->eat_limit == info->eat_limit)
	{
		info->fully_eaten++;
		if (info->fully_eaten == info->total_philo)
			info->run = 0;
	}
	if (!info->run)
		return (0);
	return (time_mcs);
}

void	manage_eat_limit(t_info *info, t_philo *philo)
{
	philo->eat_limit++;
	if (info->eat_limit && philo->eat_limit == info->eat_limit)
	{
		info->fully_eaten++;
		if (info->fully_eaten == info->total_philo)
			info->run = 0;
	}
}

void	grab_fork(t_info *info, t_philo *philo, int fork)
{
	struct timeval		time;
	unsigned long long	time_ms;

	pthread_mutex_lock(&info->m_forks[fork]);
	if (info->forks[fork / 64] & 1ULL << (fork % 64))
	{
		info->forks[fork / 64] &= ~(1ULL << fork % 64);
		pthread_mutex_unlock(&info->m_forks[fork]);
		gettimeofday(&time, NULL);
		time_ms = time.tv_sec * 1000000 + time.tv_usec;
		print_log(0, info, time_ms - info->start_mcs, philo->philo_num);
		philo->forks_held++;
	}
	else
		pthread_mutex_unlock(&info->m_forks[fork]);
}

void	return_forks(t_info *info, t_philo *philo)
{
	int	fork_1;
	int	fork_2;

	fork_1 = philo->fork_i[0];
	fork_2 = philo->fork_i[1];
	info->forks[fork_1 / 64] |= 1ULL << fork_1 % 64;
	info->forks[fork_2 / 64] |= 1ULL << fork_2 % 64;
	philo->forks_held = 0;
}
