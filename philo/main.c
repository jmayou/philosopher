/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <jmayou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:20:51 by jmayou            #+#    #+#             */
/*   Updated: 2024/12/13 12:47:52 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

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
        i++;
    }
    i = 1;
    while(str[i])
    {
        if(ft_atoi(str[i]) <= 0)
            return(1);
        i++;
    }
	return (0);
}
int allocation(t_data *data,int i)
{
    data->is_error = malloc(sizeof(int));
    if(data->is_error == NULL)
    {
        printf("Error: Failed in allocate memory\n");
        return(1);
    }
    data->philo = malloc(sizeof(t_philo) * i);
    if(data->philo == NULL)
    {
        printf("Error: Failed in allocate memory\n");
        return(free(data->is_error),1);
    }
    data->thread = malloc(sizeof(pthread_t) * i);
    if(data->philo == NULL)
    {
        printf("Error: Failed in allocate memory\n");
        return(free(data->philo),free(data->is_error),1);
    }
    data->forks = malloc(sizeof(pthread_mutex_t) * i);
    if(data->philo == NULL)
    {
        printf("Error: Failed in allocate memory\n");
        return(free(data->is_error),free(data->thread),free(data->philo),1);
    }
    return(0);
}
int    initializing(t_data *data,int ac,char **av)
{
    int i;
    int j;

    i = ft_atoi(av[1]);
    j = 0;
    if(allocation(data,i) == 1)
        return(1);
    data->is_error = 0;
    while(i > 0)
    {
        data->philo[j].data = data;
        data->philo[j].id = j;
        data->philo[j].args.max_of_meals = -1;
        data->philo[j].args.nbr_of_philo = ft_atoi(av[1]);
        data->philo[j].args.time_to_die = ft_atoi(av[2]);
        data->philo[j].args.time_to_eat = ft_atoi(av[3]);
        data->philo[j].args.time_to_sleep = ft_atoi(av[4]);
        data->philo[j].left_fork = &data->forks[data->philo[j].id];
        data->philo[j].right_fork = &data->forks[(data->philo[j].id + 1) % data->philo[j].args.nbr_of_philo];
        if(ac == 6)
            data->philo[j].args.max_of_meals = ft_atoi(av[5]);
        i--;
        j++;
    }
    return(0);
}

int init_mutex(t_data   *data)
{
    int i;

    i = 0;
    while(i < data->philo[0].args.nbr_of_philo)
    {
        if(pthread_mutex_init(&data->forks[i], NULL) != 0)
        {
            printf("Error: Failed in pthread_mutex_init\n");
            return(1);
        }
        i++;
    }
    return(0);
}

void    free_all(t_data *data)
{
    free(data->is_error);
    free(data->thread);
    free(data->philo);
    free(data->forks);
    free(data);
}
long    get_the_time(void)
{
    struct timeval tv;
    
    if(gettimeofday(&tv,NULL) == 0)
        return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
    else
        return(-1);
}
int check_is_error(t_philo  *philo)
{
    if((*philo->data->is_full) == philo->args.nbr_of_philo * philo->args.max_of_meals)
    {
        pthread_mutex_lock(&philo->data->mutex_for_print);
        printf("Philosophers are full\n");
        pthread_mutex_unlock(&philo->data->mutex_for_print);
        return(1);
    }
    else if((*philo->data->is_error) == DIED)
    {
        pthread_mutex_lock(&philo->data->mutex_for_print);
        printf("%d deid\n",philo->id + 1);
        pthread_mutex_unlock(&philo->data->mutex_for_print);
        return(1);
    }
    return(0);
}
void    go_to_sleep(t_philo *philo)
{
    long time;

    time = get_the_time();
    while(get_the_time() - time < philo->args.time_to_sleep)
    {
        usleep(50);
        if(check_is_error(philo) == 1)
            break;
    }
}
void    sleep_while_eating(t_philo *philo)
{
    long time;

    time = get_the_time();
    while(get_the_time() - time < philo->args.time_to_eat)
    {
        usleep(50);
        if(check_is_error(philo) == 1)
            break;
    }
}
void    print_message(char *str,t_philo *philo)
{
    pthread_mutex_lock(&philo->data->mutex_for_print);
    printf("%ld %d %s\n",get_the_time() - philo->data->time_start,philo->id + 1,str);
    pthread_mutex_unlock(&philo->data->mutex_for_print);
}
void    go_to_eat(t_philo *philo)
{
    philo->time_of_last_meals = get_the_time();
    while(check_is_error(philo) == 0)
    {
        print_message("is thinking\n",philo);
        pthread_mutex_lock(philo->left_fork);
        print_message("has taken a fork\n",philo);
        pthread_mutex_lock(philo->right_fork);
        print_message("has taken a fork\n",philo);
        print_message("is eating\n",philo);
        sleep_while_eating(philo);
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
    }
}
void    *one_philo(t_philo   *philo)
{
    pthread_mutex_lock(philo->left_fork);
    print_message("has taken a fork\n",philo);
    printf("%d deid\n",philo->id + 1);
    pthread_mutex_unlock(philo->left_fork);
    return(NULL);
}
void    *sumilation(void *strct)
{
    t_philo *philo;
    philo = (t_philo *)strct;
    philo->time_of_last_meals = get_the_time();
    if(philo->args.nbr_of_philo == 1)
        return(one_philo(philo));
    else
    {
        if(philo->args.nbr_of_philo % 2 == 0)
            go_to_sleep(philo);
        else
            go_to_eat(philo);    
    }
    return(NULL);
}
int    creat_thread_and_join(t_data *data)
{
    int i;

    i = 0;
    data->time_start = get_the_time();
    while(i < data->philo[i].args.nbr_of_philo)
    {
        if(pthread_create(&data->thread[i],NULL,sumilation,&data->philo[i]) != 0)
        {
            return(1);//
        }
        i++;
    }
    i = 0;
    while(i < data->philo[i].args.nbr_of_philo)
    {
        if(pthread_join(data->thread[i],NULL) != 0)
        {
            return(1);//
        }
        i++;
    }
    return(0);
}
int main(int ac,char **av)
{
    t_data  *data;

    data = malloc(sizeof(t_data));
    if(data == NULL)
        return(1);
    if((ac == 5 || ac == 6) && check_error(av) == 0)
    {
        if(initializing(data,ac,av) == 1)
            return(1);
        if(init_mutex(data) == 1)
        {
            free_all(data);
            return(1);
        }
        if(creat_thread_and_join(data) == 1)
            return(1);
    }
    else
    {
        printf("Error : Invalid arguments.\n");
        return(1);
    }
    return(0);
}
