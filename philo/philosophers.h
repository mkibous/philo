/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:33:11 by mkibous           #+#    #+#             */
/*   Updated: 2024/05/26 10:51:07 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_args
{
	int				number_of_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			number_eat;
	long			start_time;
	int				dead;
	pthread_mutex_t	philos_num_mutex;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	*forks;
	struct s_philo	*philos;
}				t_args;

typedef struct s_philo
{
	int				id;
	long			die_time;
	long			eat;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_args			*args;
	pthread_t		thread;
}				t_philo;
int		ft_parsing(t_args *args, char **argv);
long	ft_time(long start_time);
void	ft_sleep(long time);
int		ft_mutex_init(t_args *args);
void	ft_print(long time, int id, char *str, pthread_mutex_t *write_mutex);
int		chek_eat(t_args *args);
void	ft_free(t_args *args);
long	ft_atoi(char *str);
#endif 