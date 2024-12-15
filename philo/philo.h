/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <jmayou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:33:53 by jmayou            #+#    #+#             */
/*   Updated: 2024/12/15 11:21:53 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data	t_data;

typedef struct s_args
{
	int					nbr_of_philo;
	long				time_to_eat;
	long				time_to_die;
	long				time_to_sleep;
	int					max_of_meals;
}						t_args;

typedef struct s_philo
{
	int					id;
	long				time_of_last_meals;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_args				args;
	t_data				*data;
}						t_philo;

typedef struct s_data
{
	int					*is_error;
	int					*is_full;
	long				time_start;
	t_philo				*philo;
	pthread_mutex_t		*forks;
	pthread_t			*thread;
	pthread_mutex_t		mutex_for_data;
}						t_data;

long					ft_atoi(const char *str);
int						allocation(t_data *data, int i);
int						initializing(t_data *data, int ac, char **av, int i);
int						init_mutex(t_data *data);
long					get_the_time(int i);
void					sleep_while_eating(t_philo *philo, int n);
int						check_is_error(t_philo *philo);
void					observer(t_data *data);
void					go_to_sleep(t_philo *philo);
void					print_message(char *str, t_philo *philo);
void					go_to_eat(t_philo *philo);
void					*one_philo(t_philo *philo);
void					*sumilation(void *strct);
void					free_all(t_data *data);
void					cop(t_data *data);
#endif