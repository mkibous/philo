/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 10:25:07 by mkibous           #+#    #+#             */
/*   Updated: 2024/04/23 21:07:30 by mkibous          ###   ########.fr       */
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
long ft_get_current_time(long start_time)
{
    struct timeval time;
    
    gettimeofday(&time, NULL);
    return (((time.tv_sec * 1000) + (time.tv_usec / 1000)) - start_time);
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
    return (0);
}
int main(int arc, char **argv)
{
    t_args args;
    
    args.start_time = ft_get_current_time(0);
    if ((arc != 5 && arc != 6) || ft_parsing(&args, argv) == -1
        || ft_mutex_init(&args))
        return (1);
}
