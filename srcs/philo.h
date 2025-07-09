/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:15:38 by praders           #+#    #+#             */
/*   Updated: 2025/07/09 11:00:16 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define FORK_TAKEN "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DIED "died"
# define COMMAND_LINE \
	"./philo [number_of_philosophers] [time_to_die] [time_to_eat] \
[time_to_sleep] [number_of_times_each_philosopher_must_eat (optional)]\n"

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	bool			full;
	long long		last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_to_eat;
	bool			simulation_stop;
	long long		start_time;
	pthread_t		monitor;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	death_mutex;
	t_philo			*philosophers;
}					t_data;

bool				parsing(int argc);
bool				sim_stop(t_data *data);
bool				initialize_data(t_data *data);
bool				start_simulation(t_data *data);
bool				initialize_philosophers(t_data *data);
bool				str_prot(int argc, char **argv);
bool				check_zero_values(int argc, char **argv, t_data *data);
int					ft_strncmp(const char *s1, const char *s2);
long				ft_atol(const char *nptr);
long long			get_current_time(void);
void				*monitor_routine(void *arg);
void				clear_everything(t_data *data);
void				clear_forks(t_data *data, int i);
void				print_action(t_philo *philo, char *msg);

#endif