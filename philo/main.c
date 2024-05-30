/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 10:25:07 by mkibous           #+#    #+#             */
/*   Updated: 2024/05/30 18:32:19 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->philos_num_mutex);
	philo->left_fork = &philo->args->forks[philo->id];
	philo->right_fork = &philo->args->forks[(philo->id + 1)
		% philo->args->number_of_philos];
	pthread_mutex_unlock(&philo->args->philos_num_mutex);
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	ft_print(ft_time(philo->args->start_time), philo->id + 1,
		"has taken a fork", &philo->args->write_mutex);
	ft_print(ft_time(philo->args->start_time), philo->id + 1,
		"has taken a fork", &philo->args->write_mutex);
	ft_print(ft_time(philo->args->start_time), philo->id + 1,
		"is eating", &philo->args->write_mutex);
}

void	*ft_philo_thread(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (1)
	{
		eat(philo);
		pthread_mutex_lock(&philo->args->eat_mutex);
		philo->eat++;
		pthread_mutex_unlock(&philo->args->eat_mutex);
		pthread_mutex_lock(&philo->args->dead_mutex);
		philo->die_time = ft_time(philo->args->start_time)
			+ philo->args->time_to_die;
		pthread_mutex_unlock(&philo->args->dead_mutex);
		ft_sleep(philo->args->time_to_eat);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		ft_print(ft_time(philo->args->start_time), philo->id + 1,
			"is sleeping", &philo->args->write_mutex);
		ft_sleep(philo->args->time_to_sleep);
		ft_print(ft_time(philo->args->start_time), philo->id + 1,
			"is thinking", &philo->args->write_mutex);
	}
	return (NULL);
}

void	ft_philo(t_args *args)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = malloc(sizeof(t_philo) * args->number_of_philos);
	args->philos = philos;
	while (i < args->number_of_philos)
	{
		memset(&philos[i], 0, sizeof(t_philo));
		args->philos[i].id = i;
		args->philos[i].args = args;
		args->philos[i].eat = 0;
		args->philos[i].die_time = ft_time(args->start_time)
			+ args->time_to_die;
		if ((i + 1) % 2 == 0 && i > 0)
			usleep(100);
		pthread_create(&philos[i].thread, NULL, ft_philo_thread,
			(void *)&philos[i]);
		i++;
	}
}

int	while_true(t_args *args, int i)
{
	while (1)
	{
		pthread_mutex_lock(&args->eat_mutex);
		if (args->number_eat != -1 && chek_eat(args) == 0)
			return (0);
		pthread_mutex_unlock(&args->eat_mutex);
		pthread_mutex_lock(&args->dead_mutex);
		if (ft_time(args->start_time) > args->philos[i].die_time
			&& args->philos[i].die_time != 0)
		{
			pthread_mutex_unlock(&args->dead_mutex);
			pthread_mutex_lock(&args->write_mutex);
			printf("%ld %d died\n", ft_time(args->start_time), i + 1);
			usleep(500);
			return (0);
		}
		pthread_mutex_unlock(&args->dead_mutex);
		i++;
		pthread_mutex_lock(&args->philos_num_mutex);
		if (i == args->number_of_philos)
			i = 0;
		pthread_mutex_unlock(&args->philos_num_mutex);
	}
	return (1);
}

int	main(int arc, char **argv)
{
	t_args	args;
	int		i;

	i = 0;
	memset(&args, 0, sizeof(t_args));
	args.start_time = ft_time(-1);
	if ((arc != 5 && arc != 6) || ft_parsing(&args, argv) == -1
		|| ft_mutex_init(&args))
		return (1);
	ft_philo(&args);
	while_true(&args, i);
	ft_sleep(100);
	ft_free(&args);
	return (0);
}
