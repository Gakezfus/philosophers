/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_till.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Elkan Choo <echoo@42mail.sutd.edu.sg>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 18:16:12 by Elkan Choo        #+#    #+#             */
/*   Updated: 2026/02/05 18:52:46 by Elkan Choo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <sys/time.h>
#include <unistd.h>

int	wait_till(t_info *info, t_philo *philo, unsigned long long timemcs,
				unsigned long long death_mcs)
{
	struct timeval			now;
	unsigned long long		now_mcs;

	gettimeofday(&now, NULL);
	now_mcs = now.tv_sec * 1000000 + now.tv_usec;
	while (now_mcs < timemcs && !check_death(info, philo, now_mcs, death_mcs)
		&& info->run)
	{
		usleep(1000);
		gettimeofday(&now, NULL);
		now_mcs = now.tv_sec * 1000000 + now.tv_usec;
	}
	return (!info->run);
}
