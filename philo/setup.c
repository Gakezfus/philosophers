/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elkan <elkan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 16:27:08 by elkan             #+#    #+#             */
/*   Updated: 2026/01/28 22:04:26 by elkan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

void	setup(int eat_limit, char *argv[], t_info *info)
{
	long long int	num;

	pthread_mutex_init(&(info->r_mutex), NULL);
	pthread_mutex_init(&(info->p_num_mutex), NULL);
	info->philo_num = 0;
	info->total_philo = (int)ft_atoll(argv[1]);
	num = ft_atoll(argv[2]);
	info->starve_s = num / 1000LL;
	info->starve_mcs = (num % 1000LL) * 1000LL;
	num = ft_atoll(argv[3]);
	info->eat_s = num / 1000LL;
	info->eat_mcs = (num % 1000LL) * 1000LL;
	num = ft_atoll(argv[4]);
	info->sleep_s = num / 1000LL;
	info->sleep_mcs = (num % 1000LL) * 1000LL;
	if (eat_limit)
		info->eat_limit = (int)ft_atoll(argv[5]);
	return ;
}

// For dom hand, 0 is right, 1 is left, assuming clockwise seating
void	find_fork_index(t_info *info, t_philo *philo)
{
	philo->forks_held[0] = 0;
	philo->forks_held[1] = 0;
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
