/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 10:25:07 by mkibous           #+#    #+#             */
/*   Updated: 2024/05/27 18:39:23 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	eat(t_philo *philo)
{
	// pthread_mutex_lock(&philo->args->philos_num_mutex);
	// philo->left_fork = &philo->args->forks[philo->id];
	// philo->right_fork = &philo->args->forks[(philo->id + 1)
	// 	% philo->args->number_of_philos];
	// pthread_mutex_unlock(&philo->args->philos_num_mutex);
	// pthread_mutex_lock(philo->left_fork);
	// pthread_mutex_lock(philo->right_fork);
	// ft_print(ft_time(philo->args->start_time), philo->id + 1,
	// 	"has taken a fork", &philo->args->write_mutex);
	// ft_print(ft_time(philo->args->start_time), philo->id + 1,
	// 	"has taken a fork", &philo->args->write_mutex);
	// ft_print(ft_time(philo->args->start_time), philo->id + 1,
	// 	"is eating", &philo->args->write_mutex);
}

void	*ft_philo_routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	int i = 0;
	while (1)
	{
		sem_wait(philo->args->forks);
		sem_wait(philo->args->forks);
		printf("%ld %d has taken a fork\n", ft_time(philo->args->start_time), philo->id + 1);
		printf("%ld %d has taken a fork\n", ft_time(philo->args->start_time), philo->id + 1);
		printf("%ld %d is eating\n", ft_time(philo->args->start_time), philo->id + 1);
		philo->eat++;
		philo->die_time = ft_time(philo->args->start_time)
			+ philo->args->time_to_die;
		ft_sleep(philo->args->time_to_eat);
		sem_post(philo->args->forks);
		sem_post(philo->args->forks);
		printf("%ld %d is sleeping\n", ft_time(philo->args->start_time), philo->id + 1);
		ft_sleep(philo->args->time_to_sleep);
		printf("%ld %d is thinking\n", ft_time(philo->args->start_time), philo->id + 1);
	}
	return (NULL);
}

void	ft_philo(t_args *args)
{
	int		i;
	t_philo	*philos;
	pid_t	pid[args->number_of_philos];

	i = 0;
	memset(pid, 0, sizeof(pid));
	philos = malloc(sizeof(t_philo) * args->number_of_philos);
	args->philos = philos;
	sem_unlink("/forks");
	args->forks = sem_open("/forks", O_CREAT, 0644, args->number_of_philos);
	args->start_time = ft_time(-1);
	while (i < args->number_of_philos)
	{
		pid[i] = fork();
		if(pid[i] == -1)
			exit(1);
		if (pid[i] == 0)
		{
			memset(&philos[i], 0, sizeof(t_philo));
			args->philos[i].id = i;
			args->philos[i].args = args;
			args->philos[i].eat = 0;
			args->philos[i].die_time = ft_time(args->start_time)
				+ args->time_to_die;
			pthread_create(&args->philos[i].thread, NULL,
				while_true, &args->philos[i]);
			ft_philo_routine(&args->philos[i]);
		}
		else if(i + 1 == args->number_of_philos)
		{
			args->pid = pid;
			if(waitpid(-1, NULL, 0) == -1)
				exit(1);
			i = 0;
			while (i < args->number_of_philos)
			{
				kill(args->pid[i], SIGKILL);
				i++;
			}
		}
		i++;
	}
}

void	*while_true(void *args)
{
	t_philo	*philo;
	
	philo = (t_philo *)args;
	while (1)
	{
		// pthread_mutex_lock(&args->eat_mutex);
		if (philo->args->number_eat != -1 && philo->eat >= philo->args->number_eat)
		{
			exit(0);
		}
		// pthread_mutex_unlock(&args->eat_mutex);
		// pthread_mutex_lock(&args->dead_mutex);
		if (ft_time(philo->args->start_time) >= philo->die_time
			&& philo->die_time != 0)
		{
			// pthread_mutex_unlock(&args->dead_mutex);
			// pthread_mutex_lock(&args->write_mutex);
			philo->args->dead = 1;
			printf("%ld %d died\n", ft_time(philo->args->start_time), philo->id + 1);
			exit(0);
		}
		// pthread_mutex_unlock(&args->dead_mutex);
		// pthread_mutex_lock(&args->philos_num_mutex);
		// pthread_mutex_unlock(&args->philos_num_mutex);
	}
	return (NULL);
}

int	main(int arc, char **argv)
{
	t_args	args;
	int		i;

	i = 0;
	memset(&args, 0, sizeof(t_args));
	args.start_time = ft_time(-1);
	if ((arc != 5 && arc != 6) || ft_parsing(&args, argv) == -1)
		return (1);
	ft_philo(&args);
	// while_true(&args, i);
	// ft_free(&args);
	return (0);
}
