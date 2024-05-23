/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 10:25:07 by mkibous           #+#    #+#             */
/*   Updated: 2024/05/22 19:56:19 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
int ft_parsing(t_args *args, char **argv)
{
    args->number_of_philos = ft_atoi(argv[1]);
    if (args->number_of_philos < 1)
        return (-1);
    args->time_to_die = ft_atoi(argv[2]);
    if (args->time_to_die < 1)
        return (-1);
    args->time_to_eat = ft_atoi(argv[3]);
    if (args->time_to_eat < 1)
        return (-1);
    args->time_to_sleep = ft_atoi(argv[4]);
    if (args->time_to_sleep < 1)
        return (-1);
    if(argv[5])
    {
        args->number_eat = ft_atoi(argv[5]);
        if (args->number_eat < 1)
            return (-1);
    }
    else
        args->number_eat = -1;
    return (0);
}
long ft_time(long start_time)
{
    struct timeval time;
    
    gettimeofday(&time, NULL);
    if(start_time >= 0)
        return (((time.tv_sec * 1000) + (time.tv_usec / 1000)) - start_time);
    return (((time.tv_sec * 1000) + (time.tv_usec / 1000)));
}
void ft_sleep(long time)
{
    long start_time;
    
    start_time = ft_time(-1);
    while (ft_time(-1) - start_time < time)
        usleep(100);
}
int ft_mutex_init(t_args *args)
{
    int i;
    
    args->forks = malloc(sizeof(pthread_mutex_t) * args->number_of_philos);
    if (!args->forks)
        return (1);
    i = 0;
    while (i < args->number_of_philos)
    {
        if(pthread_mutex_init(&args->forks[i], NULL) != 0)
            return (1);
        i++;
    }
    if(pthread_mutex_init(&args->philos_num_mutex, NULL) != 0)
        return (1);
    if(pthread_mutex_init(&args->dead_mutex, NULL) != 0)
        return (1);
    if(pthread_mutex_init(&args->eat_mutex, NULL) != 0)
        return (1);
    if(pthread_mutex_init(&args->write_mutex, NULL) != 0)
        return (1);
    return (0);
}

void *ft_philo_thread(void *args)
{
    t_philo *philo;
    
    philo = (t_philo *)args;
    while(1)
    {
        // printf("phio %d id\n", philo->id + 1);
        pthread_mutex_lock(&philo->args->philos_num_mutex);
        philo->left_fork = &philo->args->forks[philo->id];
        philo->right_fork = &philo->args->forks[(philo->id + 1) % philo->args->number_of_philos];
        pthread_mutex_unlock(&philo->args->philos_num_mutex);
        pthread_mutex_lock(philo->left_fork);
        pthread_mutex_lock(philo->right_fork);
        pthread_mutex_lock(&philo->args->write_mutex);
        printf("%ld %d has taken a fork\n", ft_time(philo->args->start_time), philo->id + 1);
        pthread_mutex_unlock(&philo->args->write_mutex);
        pthread_mutex_lock(&philo->args->write_mutex);
        printf("%ld %d has taken a fork\n", ft_time(philo->args->start_time), philo->id + 1);
        pthread_mutex_unlock(&philo->args->write_mutex);
        pthread_mutex_lock(&philo->args->write_mutex);
        printf("%ld %d is eating\n", ft_time(philo->args->start_time), philo->id + 1);
        pthread_mutex_lock(&philo->args->eat_mutex);
        philo->eat++;
        pthread_mutex_unlock(&philo->args->eat_mutex);
        pthread_mutex_unlock(&philo->args->write_mutex);
        pthread_mutex_lock(&philo->args->dead_mutex);
        philo->die_time = ft_time(philo->args->start_time) + philo->args->time_to_die;
        pthread_mutex_unlock(&philo->args->dead_mutex);
        ft_sleep(philo->args->time_to_eat);
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_lock(&philo->args->write_mutex);
        printf("%ld %d is sleeping\n", ft_time(philo->args->start_time), philo->id + 1);
        pthread_mutex_unlock(&philo->args->write_mutex);
        ft_sleep(philo->args->time_to_sleep);
        pthread_mutex_lock(&philo->args->write_mutex);
        printf("%ld %d is thinking\n", ft_time(philo->args->start_time), philo->id + 1);
        pthread_mutex_unlock(&philo->args->write_mutex);
        // usleep(100);
    }
    return (NULL);
}
#include <libc.h>
void ft_philo(t_args *args)
{
    int i;
    t_philo *philos;
    
    i = 0;
    philos = malloc(sizeof(t_philo) * args->number_of_philos);
    args->philos = philos;
    while(i < args->number_of_philos)
    {
        memset(&philos[i], 0, sizeof(t_philo));
        args->philos[i].id = i;
        args->philos[i].args = args;
        args->philos[i].eat = 0;
        args->philos[i].die_time = ft_time(args->start_time) + args->time_to_die;
        // philos[i].thread = malloc(sizeof(pthread_t));
        if((i + 1) % 2 == 0 && i > 0)
            usleep(100);
        pthread_create(&philos[i].thread, NULL, ft_philo_thread, (void *)&philos[i]);
        i++;
    }
}
int chek_eat(t_args *args)
{
    int i;
    
    i = 0;
    while(i < args->number_of_philos)
    {
        if(args->philos[i].eat < args->number_eat)
            return (1);
        i++;
    }
    return (0);
}
void ft_free(t_args *args)
{
    int i;
    
    i = 0;
    while(i < args->number_of_philos)
    {
        pthread_mutex_destroy(&args->forks[i]);
        i++;
    }
    i = 0;
    pthread_mutex_destroy(&args->philos_num_mutex);
    pthread_mutex_destroy(&args->dead_mutex);
    pthread_mutex_destroy(&args->eat_mutex);
    pthread_mutex_destroy(&args->write_mutex);
    free(args->forks);
    free(args->philos);
}
int while_true( t_args *args, int i)
{
    while (1)
    {
        pthread_mutex_lock(&args->eat_mutex);
        if(args->number_eat != -1 && chek_eat(args) == 0 )
            return (0);
        pthread_mutex_unlock(&args->eat_mutex);
        pthread_mutex_lock(&args->dead_mutex);
        if(ft_time(args->start_time) > args->philos[i].die_time
            && args->philos[i].die_time != 0)
        {
            pthread_mutex_unlock(&args->dead_mutex);
            pthread_mutex_lock(&args->write_mutex);
            printf("%ld %d died\n", ft_time(args->start_time), i + 1);
            // ft_sleep(10);
            return (0);
        }
        pthread_mutex_unlock(&args->dead_mutex);
        i++;
        pthread_mutex_lock(&args->philos_num_mutex);
        if(i == args->number_of_philos)
            i = 0;
        pthread_mutex_unlock(&args->philos_num_mutex);
        usleep(100);
    }
    return (1);
}
int main(int arc, char **argv)
{
    t_args args;
    int i;

    i = 0;
    memset(&args, 0, sizeof(t_args));
    args.start_time = ft_time(-1);
    if ((arc != 5 && arc != 6) || ft_parsing(&args, argv) == -1
        || ft_mutex_init(&args))
        return (1);
    ft_philo(&args);
    while_true(&args, i);
    ft_free(&args);
    return (0);
}
