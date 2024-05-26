/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:32:31 by mkibous           #+#    #+#             */
/*   Updated: 2024/05/26 20:15:37 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

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

void	ft_print(long time, int id, char *str)
{
	// pthread_mutex_lock(mutex);
	printf("%ld %d %s\n", time, id, str);
	// pthread_mutex_unlock(mutex);
}
