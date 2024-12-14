/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <jmayou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 19:31:27 by jmayou            #+#    #+#             */
/*   Updated: 2024/12/14 19:42:25 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	go_to_sleep(t_philo *philo)
{
	long	time;

	time = get_the_time(1);
	while (get_the_time(1) - time < philo->args.time_to_sleep * 1000)
	{
		usleep(50);
		if (check_is_error(philo) == 1)
			break ;
	}
}

void	print_message(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_for_data);
	printf("%ld %d %s", get_the_time(0) - philo->data->time_start, philo->id
		+ 1, str);
	pthread_mutex_unlock(&philo->data->mutex_for_data);
}

void	go_to_eat(t_philo *philo)
{
	philo->time_of_last_meals = get_the_time(0);
	print_message("is thinking\n", philo);
	pthread_mutex_lock(philo->left_fork);
	print_message("has taken a fork\n", philo);
	pthread_mutex_lock(philo->right_fork);
	print_message("has taken a fork\n", philo);
	print_message("is eating\n", philo);
	sleep_while_eating(philo, philo->args.time_to_eat);
	pthread_mutex_lock(&philo->data->mutex_for_data);
	(*philo->data->is_full) += 1;
	pthread_mutex_unlock(&philo->data->mutex_for_data);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_message("has taken a fork\n", philo);
	print_message("is thinking\n", philo);
	sleep_while_eating(philo, philo->args.time_to_die);
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}

void	*sumilation(void *strct)
{
	t_philo	*philo;

	philo = (t_philo *)strct;
	philo->time_of_last_meals = get_the_time(0);
	if (philo->args.nbr_of_philo == 1)
		return (one_philo(philo));
	if (philo->id % 2 == 0)
	{
		print_message(" is sleeping\n", philo);
		go_to_sleep(philo);
	}
	while (check_is_error(philo) == 0)
	{
		go_to_eat(philo);
		print_message("is sleeping\n", philo);
		go_to_sleep(philo);
	}
	return (NULL);
}
