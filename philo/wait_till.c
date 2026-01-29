/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_till.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Elkan Choo <echoo@42mail.sutd.edu.sg>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 18:16:12 by Elkan Choo        #+#    #+#             */
/*   Updated: 2026/01/29 18:55:34 by Elkan Choo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>

void	wait_till(long long unsigned int time_ms, long long unsigned int death)
{
	struct timeval			now;
	long long unsigned int	now_ms;

	gettimeofday(&now, NULL);
	now_ms = now.tv_sec * 1000000 + now.tv_usec;
	while (now_ms < time_ms)
	{
		usleep(1000);
		gettimeofday(&now, NULL);
		now_ms = now.tv_sec * 1000000 + now.tv_usec;
	}
	return ;
}
