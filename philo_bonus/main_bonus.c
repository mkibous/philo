/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 10:25:07 by mkibous           #+#    #+#             */
/*   Updated: 2024/05/30 18:30:46 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	ft_fork(t_philo *philo)
{
	sem_wait(philo->args->forks);
	ft_print(ft_time(philo->args->start_time), philo->id + 1,
		"has taken a fork", philo->args->print);
	sem_wait(philo->args->forks);
	ft_print(ft_time(philo->args->start_time), philo->id + 1,
		"has taken a fork", philo->args->print);
}

void	*ft_philo_routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (1)
	{
		ft_fork(philo);
		ft_print(ft_time(philo->args->start_time), philo->id + 1,
			"is eating", philo->args->print);
		philo->eat++;
		philo->die_time = ft_time(philo->args->start_time)
			+ philo->args->time_to_die;
		ft_sleep(philo->args->time_to_eat);
		sem_post(philo->args->forks);
		sem_post(philo->args->forks);
		ft_print(ft_time(philo->args->start_time), philo->id + 1,
			"is sleeping", philo->args->print);
		ft_sleep(philo->args->time_to_sleep);
		ft_print(ft_time(philo->args->start_time), philo->id + 1,
			"is thinking", philo->args->print);
	}
	return (NULL);
}

void	ft_philo(t_args *args)
{
	int		i;
	pid_t	*pid;

	i = 0;
	pid = malloc(sizeof(pid_t) * args->number_of_philos);
	memset(pid, 0, sizeof(pid_t) * args->number_of_philos);
	args->pid = pid;
	while (i < args->number_of_philos)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			exit(1);
		if (pid[i] == 0)
			ft_child(args, i);
		else if (i + 1 == args->number_of_philos)
		{
			if (waitpid(-1, NULL, 0) == -1)
				exit(1);
			ft_kill(args);
			return ;
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
		if (philo->args->number_eat != -1
			&& philo->eat >= philo->args->number_eat)
			exit(0);
		if (ft_time(philo->args->start_time) >= philo->die_time
			&& philo->die_time != 0)
		{
			philo->args->dead = 1;
			sem_wait(philo->args->print);
			printf("%ld %d died\n", ft_time(philo->args->start_time),
				philo->id + 1);
			exit(0);
		}
	}
	return (NULL);
}

int	main(int arc, char **argv)
{
	t_args	args;
	t_philo	*philos;
	int		i;

	i = 0;
	memset(&args, 0, sizeof(t_args));
	args.start_time = ft_time(-1);
	if ((arc != 5 && arc != 6) || ft_parsing(&args, argv) == -1)
		return (1);
	philos = malloc(sizeof(t_philo) * args.number_of_philos);
	args.philos = philos;
	sem_unlink("/forks");
	sem_unlink("/print");
	args.forks = sem_open("/forks", O_CREAT, 0644, args.number_of_philos);
	args.print = sem_open("/print", O_CREAT, 0644, 1);
	args.start_time = ft_time(-1);
	ft_philo(&args);
	ft_free(&args);
	return (0);
}
