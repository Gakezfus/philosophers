/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Elkan Choo <echoo@42mail.sutd.edu.sg>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 12:00:00 by elkan             #+#    #+#             */
/*   Updated: 2026/01/29 18:55:37 by Elkan Choo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdint.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct information
{
	long long unsigned int	start_mcs;
	long long unsigned int	eat_mcs;
	long long unsigned int	sleep_mcs;
	long long unsigned int	starve_mcs;
	uint64_t				*forks;
	pthread_mutex_t			*m_forks;
	int						total_philo;
	int						philo_num;
	pthread_mutex_t			p_num_mutex;
	int						eat_limit;
	int						run;
	pthread_mutex_t			print_mutex;
	pthread_mutex_t			r_mutex;
}	t_info;

typedef struct philosopher
{
	long long unsigned int	die_time_mcs;
	long long unsigned int	sleep_time_mcs;
	long long unsigned int	wake_time_mcs;
	long long unsigned int	eat_time_mcs;
	int						philo_num;
	int						dom_hand;
	int						fork_i[2];
	uint8_t					forks_held;
	int						number;
	int						eat_limit;
}	t_philo;

// from ft_atoll.c
long long int				ft_atoll(const char *str);

// from setup.c
void						setup(int eat_limit, char *argv[], t_info *data);
void						find_fork_index(t_info *info, t_philo *philo);

// from phillosophers.c
void						*philosopher_act(void *i);

// from print_log.c
void						print_log(int act, pthread_mutex_t print_mutex,
								struct timeval time, int philo_num);
// from wait_till.c
void						wait_till(long long unsigned int time_ms,
								long long unsigned int death);

// from eating.c
void						eating(t_info *info, t_philo *philo);
void						return_forks(t_info *info, t_philo *philo);

#endif
