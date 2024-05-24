/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:36:16 by mkibous           #+#    #+#             */
/*   Updated: 2024/05/24 15:46:03 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

void	ft_free(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->number_of_philos)
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
