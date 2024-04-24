#ifndef PHILOSOPHERS_H
#define  PHILOSOPHERS_H
#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>//memset
#include <unistd.h>//usleep write
long	ft_atoi(char *str);

typedef struct s_args
{
    int number_of_philos;
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
    long number_eat;
    long start_time;
    int dead;
    pthread_mutex_t print;
    pthread_mutex_t *forks;
    struct s_philo *philos;
}				t_args;

typedef struct s_philo
{
    int id;
    long die_time;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    t_args *args;
    pthread_t thread;
}				t_philo;
#endif 