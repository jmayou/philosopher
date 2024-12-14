/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <jmayou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:20:51 by jmayou            #+#    #+#             */
/*   Updated: 2024/12/14 19:34:59 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

void leaks(void)
{
    system("leaks philo");
}

int	check_error(char **str)
{
	int	i;
    int  j;

	i = 1;
    while(str[i])
    {
        j = 0;
	    while (str[i][j])
	    {
	    	if ((str[i][j] <= '9' && str[i][j] >= '0'))
	    		j++;
	    	else
	    		return(1);
	    }
        if(ft_atoi(str[i]) <= 0)
            return(1);
        i++;
    }
    
	return (0);
}
int initializing_and_init_mutex(t_data *data,int ac,char **av)
{
    if(initializing(data,ac,av) == 1)
        return(1);
    if(init_mutex(data) == 1)
    {
        free_all(data);
        return(1);
    }
    return(0);
}
int    creat_thread_and_join(t_data *data)
{
    int i;

    i = 0;
    data->time_start = get_the_time(0);
    while(i < data->philo[0].args.nbr_of_philo)
    {   
        if(pthread_create(&data->thread[i],NULL,sumilation,&data->philo[i]) != 0)
            return(1);  
        i++;
    }
    i = 0;
    while(i < data->philo[0].args.nbr_of_philo)
    {
        if(pthread_join(data->thread[i],NULL) != 0)
            return(1);
        i++;
    }
    observer(data);
    return(0);
}

void    free_all(t_data *data)
{
    int i;

    i = 0;
    while(i < data->philo[0].args.nbr_of_philo)
    {
        pthread_mutex_destroy(&data->forks[i]);
        i++;
    }
    pthread_mutex_destroy(&data->mutex_for_data  );
    free(data->is_error);
    free(data->is_full);
    free(data->thread);
    free(data->philo);
    free(data->forks);
    free(data);
}

int main(int ac,char **av)
{
    t_data  *data;

    atexit(leaks);

    data = malloc(sizeof(t_data));
    if(data == NULL)
        return(1);
    if((ac == 5 || ac == 6) && check_error(av) == 0)
    {
        if(initializing_and_init_mutex(data,ac,av) == 1)
            return (1);
        if(creat_thread_and_join(data) == 1)
        {
			free_all(data);
			return (1);
		}
    }
    else
    {
        free(data);
        printf("Error : Invalid arguments.\n");
        return(1);
    }
    free_all(data);
    return(0);
}
