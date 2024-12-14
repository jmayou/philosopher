/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <jmayou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 19:26:54 by jmayou            #+#    #+#             */
/*   Updated: 2024/12/14 19:27:43 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_is_error(t_philo  *philo)
{
    long time;

    time = get_the_time(0); 
    pthread_mutex_lock(&philo->data->mutex_for_data);
    if(*philo->data->is_error != -1)
    {
        pthread_mutex_unlock(&philo->data->mutex_for_data);
        return(1);
    }
    if(philo->args.max_of_meals != -1 && (*philo->data->is_full) >= philo->args.nbr_of_philo * philo->args.max_of_meals)
    {
        pthread_mutex_unlock(&philo->data->mutex_for_data); 
        return(1);
    }
    if ((time - philo->time_of_last_meals) >= philo->args.time_to_die)
	{
		*philo->data->is_error = philo->id + 1;
        pthread_mutex_unlock(&philo->data->mutex_for_data);
		return (1);
	}
    pthread_mutex_unlock(&philo->data->mutex_for_data);
    return(0);
}
void    observer(t_data *data)
{
    pthread_mutex_lock(&data->mutex_for_data);
    if((*data->is_error) != -1)
        printf("%ld %d is deid\n",get_the_time(0) - data->time_start,(*data->is_error));
    pthread_mutex_unlock(&data->mutex_for_data);
}
