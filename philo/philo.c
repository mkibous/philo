/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:32:31 by mkibous           #+#    #+#             */
/*   Updated: 2024/06/08 23:39:59 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_parsing(t_args *args, char **argv)
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
	if (argv[5])
	{
		args->number_eat = ft_atoi(argv[5]);
		if (args->number_eat < 1)
			return (-1);
	}
	else
		args->number_eat = -1;
	return (0);
}

long	ft_time(long start_time)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	if (start_time >= 0)
		return (((time.tv_sec * 1000) + (time.tv_usec / 1000)) - start_time);
	return (((time.tv_sec * 1000) + (time.tv_usec / 1000)));
}

void	ft_sleep(long time)
{
	long	start_time;

	start_time = ft_time(-1);
	while (ft_time(-1) - start_time < time)
		usleep(100);
}

int	ft_mutex_init(t_args *args)
{
	int	i;

	args->forks = malloc(sizeof(pthread_mutex_t) * args->number_of_philos);
	if (!args->forks)
		return (1);
	i = 0;
	while (i < args->number_of_philos)
	{
		if (pthread_mutex_init(&args->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_init(&args->philos_num_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&args->dead_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&args->eat_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&args->write_mutex, NULL) != 0)
		return (1);
	return (0);
}

void	ft_print(long time, int id, char *str, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	printf("%ld %d %s\n", time, id, str);
	pthread_mutex_unlock(mutex);
}
