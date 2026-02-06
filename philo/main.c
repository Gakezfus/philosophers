/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Elkan Choo <echoo@42mail.sutd.edu.sg>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 11:49:21 by elkan             #+#    #+#             */
/*   Updated: 2026/02/06 17:14:05 by Elkan Choo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

int	check_input(int argc, char *argv[]);
int	run_threads(t_info *info, pthread_t *philo);

// TODO: Make Norm compliant
int	main(int argc, char *argv[])
{
	int			index;
	t_info		info;
	pthread_t	*philo;

	if (argc < 5 || argc > 6)
	{
		write(2, "Format: ./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep \
number_of_times_each_philosopher_must_eat (optional)\n", 130);
		return (1);
	}
	if (check_input(argc, argv))
		return (1);
	setup(argc - 5, argv, &info);
	philo = malloc(info.total_philo * sizeof(pthread_t));
	if (philo == NULL || info.forks == NULL || info.m_forks == NULL)
		return (write(2, "Memory error\n", 1), 1);
	if (run_threads(&info, philo))
		return (1);
	index = 0;
	while (index < info.total_philo)
	{
		pthread_join(philo[index++], NULL);
	}
	shutdown(&info, philo);
}

int	check_input(int argc, char *argv[])
{
	int				index_1;
	int				index_2;
	long long int	num;

	index_1 = 1;
	while (index_1 < argc)
	{
		index_2 = 0;
		while (argv[index_1][index_2])
		{
			if (argv[index_1][index_2] < '0' || '9' < argv[index_1][index_2])
				return (write(2, "All characters must be numbers\n", 32), 1);
			num = ft_atoll(argv[index_1]);
			if (num <= 0)
				return (write(2, "Numbers <= 0 or over/underflow\n", 32), 1);
			index_2++;
		}
		index_1++;
	}
	return (0);
}

int	run_threads(t_info *info, pthread_t *philo)
{
	int	index;

	pthread_mutex_lock(&(info->r_mutex));
	index = 0;
	while (index < info->total_philo)
	{
		pthread_mutex_init(&(info->m_forks[index]), NULL);
		if (pthread_create(&(philo[index++]), NULL,
				philosopher_act, (void *)info))
			return (pthread_mutex_unlock(&(info->r_mutex)),
				write(2, "Thread creation error\n", 23), 1);
	}
	pthread_mutex_unlock(&(info->r_mutex));
	return (0);
}
