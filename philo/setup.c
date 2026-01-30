/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Elkan Choo <echoo@42mail.sutd.edu.sg>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 16:27:08 by elkan             #+#    #+#             */
/*   Updated: 2026/01/30 19:13:34 by Elkan Choo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <pthread.h>
#include <sys/time.h>
#include <string.h>

void	setup(int eat_limit, char *argv[], t_info *info);
void	philo_setup(t_info *info, t_philo *philo);

void	setup(int eat_limit, char *argv[], t_info *info)
{
	long long int	num;

	pthread_mutex_init(&(info->r_mutex), NULL);
	pthread_mutex_init(&(info->p_num_mutex), NULL);
	pthread_mutex_init(&(info->print_mutex), NULL);
	info->forks = malloc((info->total_philo / 64 + 1) * sizeof(uint64_t));
	memset(info->forks, 0xFF, (info->total_philo / 64 + 1) * sizeof(uint64_t));
	info->m_forks = malloc((info->total_philo) * sizeof(pthread_mutex_t));
	info->philo_num = 0;
	info->total_philo = (int)ft_atoll(argv[1]);
	num = ft_atoll(argv[2]);
	info->starve_mcs = num * 1000ULL;
	num = ft_atoll(argv[3]);
	info->eat_mcs = num * 1000ULL;
	num = ft_atoll(argv[4]);
	info->sleep_mcs = num * 1000ULL;
	if (eat_limit)
		info->eat_limit = (int)ft_atoll(argv[5]);
	info->run = 1;
	info->end_mcs = 0;
	return ;
}

void	set_start_time(t_info *info)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	info->start_mcs = time.tv_sec * 1000000 + time.tv_usec;
}

// For dom hand, 0 is right, 1 is left, assuming clockwise seating
void	philo_setup(t_info *info, t_philo *philo)
{
	philo->die_mcs = info->start_mcs + info->starve_mcs;
	philo->dom_hand = philo->philo_num % 2;
	philo->forks_held = 0;
	if (philo->philo_num != info->total_philo)
	{
		philo->fork_i[philo->dom_hand] = philo->philo_num;
		philo->fork_i[!philo->dom_hand] = philo->philo_num + 1;
	}
	else
	{
		philo->fork_i[philo->dom_hand] = philo->philo_num;
		philo->fork_i[!philo->dom_hand] = 0;
	}
}
