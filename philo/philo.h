/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elkan <elkan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 12:00:00 by elkan             #+#    #+#             */
/*   Updated: 2026/01/28 22:03:31 by elkan            ###   ########.fr       */
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
	suseconds_t		eat_mcs;
	time_t			eat_s;
	suseconds_t		sleep_mcs;
	time_t			sleep_s;
	suseconds_t		starve_mcs;
	time_t			starve_s;
	uint64_t		*forks;
	pthread_mutex_t	*m_forks;
	int				total_philo;
	int				philo_num;
	pthread_mutex_t	p_num_mutex;
	int				eat_limit;
	int				run;
	pthread_mutex_t	r_mutex;
}	t_info;

typedef struct philosopher
{
	suseconds_t		die_time_mcs;
	time_t			die_time_s;
	suseconds_t		sleep_time_mcs;
	time_t			sleep_time_s;
	suseconds_t		think_time_mcs;
	time_t			think_time_s;
	int				philo_num;
	int				dom_hand;
	int				sync;
	int				fork_i[2];
	int				forks_held[2];
	int				even;
	int				number;
	int				eat_limit;
}	t_philo;

// from ft_atoll.c
long long int	ft_atoll(const char *str);

// from setup.c
void			setup(int eat_limit, char *argv[], t_info *data);
void			find_fork_index(t_info *info, t_philo *philo);

// from phillosophers.c
void			*philosopher_act(void *i);

#endif
