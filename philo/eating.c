/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elkan <elkan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 21:34:19 by elkan             #+#    #+#             */
/*   Updated: 2026/01/28 22:40:27 by elkan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// For dom hand, 0 is right, 1 is left, assuming clockwise seating
void	eating(t_info *info, t_philo *philo)
{
	int	fork_1;
	int	fork_2;

	fork_1 = philo->fork_i[0];
	fork_2 = philo->fork_i[1];
	while (philo->forks_held != 0b11)
	{
		pthread_mutex_lock(&info->m_forks[fork_1]);
		if (info->forks[fork_1 / 64]
			& 1ULL << (fork_1 % 64))
		{
			info->forks[fork_1 / 64]
				&= info->forks[fork_1 / 64] - 1ULL;
			pthread_mutex_unlock(&info->m_forks[fork_1]);
			philo->forks_held = 0b01;
		}
		else
			pthread_mutex_unlock(&info->m_forks[fork_1]);
		if (philo->forks_held == 0b1)
		{
			pthread_mutex_lock(&info->m_forks[fork_2]);
			if (info->forks[fork_2 / 64]
			& 1ULL << (fork_2 % 64))
			{
				info->forks[fork_2 / 64]
					&= info->forks[fork_2 / 64] - 1ULL;
				pthread_mutex_unlock(&info->m_forks[fork_2]);
				philo->forks_held = 0b11;
			}
			else
				pthread_mutex_unlock(&info->m_forks[fork_2]);
		}
	}
	// print success
	// at time of finishing eating, put down forks
}
