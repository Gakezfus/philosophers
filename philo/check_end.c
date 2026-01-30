/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Elkan Choo <echoo@42mail.sutd.edu.sg>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 14:31:39 by Elkan Choo        #+#    #+#             */
/*   Updated: 2026/01/30 19:13:28 by Elkan Choo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_info *info, t_philo *philo, unsigned long long now_mcs,
		unsigned long long death_mcs);

// This function checks if the philosopher calling this function has died.
int	check_death(t_info *info, t_philo *philo, unsigned long long now_mcs,
		unsigned long long death_mcs)
{
	if (now_mcs >= death_mcs)
	{
		print_log(1, info->print_mutex, death_mcs, philo->philo_num);
		return (1);
	}
	return (0);
}
