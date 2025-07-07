/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: praders <praders@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:15:38 by praders           #+#    #+#             */
/*   Updated: 2025/07/07 15:26:32 by praders          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define FORK_TAKEN "has taken a fork"
#define EATING "is eating"
#define SLEEPING "is sleeping"
#define THINKING "is thinking"
#define DIED "died"

typedef struct s_philo
{
    int id;
    int meals_eaten;
    bool full;
    long long last_meal_time;
    pthread_t   thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    t_data *data;
}   t_philo;

typedef struct s_data
{
    int num_philos;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int meals_to_eat;
    bool simulation_stop;
    long long start_time;
    pthread_mutex_t *forks;
    pthread_mutex_t write_mutex;
    pthread_mutex_t meal_mutex;
    pthread_mutex_t death_mutex;
    t_philo *philosophers;
}   t_data;


#endif