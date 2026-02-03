/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elkan <elkan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 14:31:39 by Elkan Choo        #+#    #+#             */
/*   Updated: 2026/02/03 21:30:31 by elkan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_info *info, t_philo *philo, unsigned long long *now_mcs,
		unsigned long long death_mcs);

// This function checks if the philosopher calling this function has died.
int	check_death(t_info *info, t_philo *philo, unsigned long long *now_mcs,
		unsigned long long death_mcs)
{
	if (*now_mcs >= death_mcs)
	{
		print_log(1, info->print_mutex, death_mcs, philo->philo_num);
		info->run = 0;
		info->end_mcs = death_mcs;
		return (1);
	}
	return (0);
}
