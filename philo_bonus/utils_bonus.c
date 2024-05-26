/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:36:16 by mkibous           #+#    #+#             */
/*   Updated: 2024/05/26 15:15:19 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	chek_eat(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->number_of_philos)
	{
		printf("args->philos[i].eat: %d\n", args->philos[i].eat);
		if (args->philos[i].eat < args->number_eat)
			return (1);
		i++;
	}
	return (0);
}

void	ft_free(t_args *args)
{
	free(args->philos);
}
