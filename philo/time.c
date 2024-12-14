/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <jmayou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 19:23:38 by jmayou            #+#    #+#             */
/*   Updated: 2024/12/14 19:43:49 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_the_time(int i)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	if (i == 0)
		return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	else
		return (tv.tv_sec * 1000000 + tv.tv_usec);
}

void	sleep_while_eating(t_philo *philo, int n)
{
	long	time;

	time = get_the_time(1);
	while (get_the_time(1) - time < n * 1000)
	{
		usleep(50);
		if (check_is_error(philo) == 1)
			break ;
	}
}
