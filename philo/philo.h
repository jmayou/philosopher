/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <jmayou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:33:53 by jmayou            #+#    #+#             */
/*   Updated: 2024/12/12 21:44:02 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

# define DIED 1
# define FULL 2
# define ERROR 3

typedef struct s_args
{
    int				nbr_of_philo;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
    int				max_of_meals;
}   t_args;

typedef struct s_philo
{
    int id;
    long				time_of_last_meals;
    pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
    t_args  args;
}   t_philo;

typedef struct s_data
{
    int				*is_error;
    int             *is_full;
    long    time_start;
    t_philo *philo;
    pthread_mutex_t *forks;
    pthread_t		*thread;
    pthread_mutex_t mutex_for_print;
    pthread_mutex_t mutex_for_error;
    pthread_mutex_t mutex_for_time;
}   t_data;




#endif