/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <jmayou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 22:16:49 by jmayou            #+#    #+#             */
/*   Updated: 2024/12/14 19:50:07 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_atoi(int *i, int *k, long *nb)
{
	*i = 0;
	*nb = 0;
	*k = 0;
}

long	ft_atoi(const char *str)
{
	int		i;
	int		k;
	long	nb;

	init_atoi(&i, &k, &nb);
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
		i++;
	if (str[i] == '-')
		return (-1);
	else if (str[i] == '+')
		i++;
	k = i;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		i++;
	}
	i = k;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		nb = (nb * 10) + (str[i++] - '0');
	if (nb > 2147483647)
		return (-1);
	return (nb);
}

int	allocation(t_data *data, int i)
{
	data->is_error = malloc(sizeof(int));
	if (data->is_error == NULL)
		return (printf("Error: Failed to allocate memory\n"), 1);
	data->is_full = malloc(sizeof(int));
	if (data->is_full == NULL)
		return (printf("Error: Failed to allocate memory\n"),
			free(data->is_error), 1);
	data->philo = malloc(sizeof(t_philo) * i);
	if (data->philo == NULL)
		return (printf("Error: Failed to allocate memory\n"),
			free(data->is_error), free(data->is_full), 1);
	data->thread = malloc(sizeof(pthread_t) * i);
	if (data->thread == NULL)
		return (printf("Error: Failed to allocate memory\n"),
			free(data->is_error), free(data->is_full), free(data->philo), 1);
	data->forks = malloc(sizeof(pthread_mutex_t) * i);
	if (data->forks == NULL)
		return (printf("Error: Failed to allocate memory\n"),
			free(data->is_error), free(data->is_full), free(data->philo),
			free(data->thread), 1);
	return (0);
}

int	initializing(t_data *data, int ac, char **av, int i)
{
	int	j;

	j = 0;
	if (allocation(data, i) == 1)
		return (1);
	*data->is_error = -1;
	*data->is_full = -1;
	while (--i > 0)
	{
		data->philo[j].data = data;
		data->philo[j].id = j;
		data->philo[j].args.max_of_meals = -1;
		data->philo[j].args.nbr_of_philo = ft_atoi(av[1]);
		data->philo[j].args.time_to_die = ft_atoi(av[2]);
		data->philo[j].args.time_to_eat = ft_atoi(av[3]);
		data->philo[j].args.time_to_sleep = ft_atoi(av[4]);
		data->philo[j].left_fork = &data->forks[data->philo[j].id];
		data->philo[j].right_fork = &data->forks[(data->philo[j].id + 1)
			% data->philo[j].args.nbr_of_philo];
		if (ac == 6)
			data->philo[j].args.max_of_meals = ft_atoi(av[5]);
		j++;
	}
	return (0);
}

int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo[0].args.nbr_of_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			printf("Error: Failed in pthread_mutex_init\n");
			while (i >= 0)
				pthread_mutex_destroy(&data->forks[i]);
			return (1);
		}
		i++;
	}
	if (pthread_mutex_init(&data->mutex_for_data, NULL) != 0)
	{
		printf("Error: Failed in pthread_mutex_init\n");
		return (1);
	}
	return (0);
}
