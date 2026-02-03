/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elkan <elkan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 21:34:19 by elkan             #+#    #+#             */
/*   Updated: 2026/02/03 21:30:32 by elkan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <sys/time.h>
#include <unistd.h>

unsigned long long	eating(t_info *info, t_philo *philo);
void				return_forks(t_info *info, t_philo *philo);

void	grab_fork(t_info *info, t_philo *philo, int fork);

// For dom hand, 0 is right, 1 is left, assuming clockwise seating
unsigned long long eating(t_info *info, t_philo *philo)
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
			&time_mcs, info->starve_mcs))
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
	return (time_mcs);
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
		print_log(0, info->print_mutex, time_ms, philo->philo_num);
		philo->forks_held++;
	}
	else
		pthread_mutex_unlock(&info->m_forks[fork]);
	philo->eat_limit++;
	if (philo->eat_limit == info->eat_limit)
		info->fully_eaten++;
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
