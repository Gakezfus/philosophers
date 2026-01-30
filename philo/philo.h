/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Elkan Choo <echoo@42mail.sutd.edu.sg>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 12:00:00 by elkan             #+#    #+#             */
/*   Updated: 2026/01/30 19:13:31 by Elkan Choo       ###   ########.fr       */
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
	unsigned long long	start_mcs;
	unsigned long long	eat_mcs;
	unsigned long long	sleep_mcs;
	unsigned long long	starve_mcs;
	unsigned long long	end_mcs;
	uint64_t			*forks;
	pthread_mutex_t		*m_forks;
	int					total_philo;
	int					philo_num;
	pthread_mutex_t		p_num_mutex;
	int					eat_limit;
	int					fully_eaten;
	uint8_t				run;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		r_mutex;
}	t_info;

typedef struct philosopher
{
	unsigned long long	die_mcs;
	unsigned long long	sleep_mcs;
	unsigned long long	wake_mcs;
	unsigned long long	eat_mcs;
	int					philo_num;
	uint8_t				dom_hand;
	uint8_t				fork_i[2];
	uint8_t				forks_held;
	int					number;
	int					eat_limit;
}	t_philo;

// from ft_atoll.c
long long int	ft_atoll(const char *str);

// from setup.c
void			setup(int eat_limit, char *argv[], t_info *data);
void			find_fork_index(t_info *info, t_philo *philo);

// from phillosophers.c
void			*philosopher_act(void *i);
void			update_times(info, philo, time);

// from print_log.c
int				print_log(int act, pthread_mutex_t print_mutex,
					unsigned long long now_mcs, int philo_num);
// from wait_till.c
int				wait_till(t_info *info, unsigned long long time_ms,
					unsigned long long death_ms);

// from eating.c
struct timeval	eating(t_info *info, t_philo *philo);
void			return_forks(t_info *info, t_philo *philo);

// from check_end.c
int				check_death(t_info *info, t_philo *philo,
					unsigned long long now_mcs,
					unsigned long long death_mcs);

#endif
