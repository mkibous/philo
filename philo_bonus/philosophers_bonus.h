/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:33:11 by mkibous           #+#    #+#             */
/*   Updated: 2024/06/08 15:31:28 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <semaphore.h>
# include <signal.h>
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
	pid_t			*pid;
	sem_t			*forks;
	sem_t			*print;
	struct s_philo	*philos;
}				t_args;

typedef struct s_philo
{
	int				id;
	long			die_time;
	long			eat;
	sem_t			*time;
	pthread_t		thread;
	t_args			*args;
}				t_philo;
int		ft_parsing(t_args *args, char **argv);
long	ft_time(long start_time);
void	ft_sleep(long time);
int		chek_eat(t_args *args);
long	ft_atoi(char *str);
void	*while_true(void *args);
void	ft_print(long time, int id, char *str, sem_t *print);
void	ft_kill(t_args *args);
void	ft_child(t_args *args, int i);
void	ft_free(t_args *args);
void	*ft_philo_routine(void *args);
void	ft_wait(t_args *args);
#endif