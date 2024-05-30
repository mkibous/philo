/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:36:16 by mkibous           #+#    #+#             */
/*   Updated: 2024/05/30 18:31:43 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	chek_eat(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->number_of_philos)
	{
		if (args->philos[i].eat < args->number_eat)
			return (1);
		i++;
	}
	return (0);
}

void	ft_kill(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->number_of_philos)
	{
		kill(args->pid[i], SIGKILL);
		i++;
	}
}

void	ft_child(t_args *args, int i)
{
	memset(&args->philos[i], 0, sizeof(t_philo));
	args->philos[i].id = i;
	args->philos[i].args = args;
	args->philos[i].eat = 0;
	args->philos[i].die_time = ft_time(args->start_time)
		+ args->time_to_die;
	pthread_create(&args->philos[i].thread, NULL,
		while_true, &args->philos[i]);
	ft_philo_routine(&args->philos[i]);
}

void	ft_free(t_args *args)
{
	sem_close(args->forks);
	sem_close(args->print);
	free(args->pid);
	free(args->philos);
}
