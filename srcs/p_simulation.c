/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_simulation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:46:05 by mprazere          #+#    #+#             */
/*   Updated: 2025/07/10 16:18:20 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat_philo(t_philo *philo)
{
	if (philo->left_fork < philo->right_fork)
	{
		philo->first_fork = philo->left_fork;
		philo->second_fork = philo->right_fork;
	}
	else
	{
		philo->first_fork = philo->right_fork;
		philo->second_fork = philo->left_fork;
	}
	pthread_mutex_lock(philo->first_fork);
	print_action(philo, FORK_TAKEN);
	pthread_mutex_lock(philo->second_fork);
	print_action(philo, FORK_TAKEN);
	print_action(philo, EATING);
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal_time = get_current_time();
	philo->meals_eaten++;
	if (philo->data->meals_to_eat > 0
		&& philo->meals_eaten == philo->data->meals_to_eat)
		philo->full = true;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
}

static void	sleep_philo(t_philo *philo)
{
	print_action(philo, SLEEPING);
	usleep(philo->data->time_to_sleep * 1000);
}

static void	think_philo(t_philo *philo)
{
	long long	time_to_think;

	print_action(philo, THINKING);
	time_to_think = (philo->data->time_to_die - (philo->data->time_to_eat
				+ philo->data->time_to_sleep)) / 2;
	if (time_to_think < 0)
		time_to_think = 0;
	usleep(time_to_think * 1000);
}

static void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->num_philos == 1)
	{
		print_action(philo, FORK_TAKEN);
		usleep(philo->data->time_to_die * 1000);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(1000);
	while (sim_stop(philo->data) == false)
	{
		eat_philo(philo);
		sleep_philo(philo);
		think_philo(philo);
	}
	return (NULL);
}

bool	start_simulation(t_data *data)
{
	int	i;

	data->start_time = get_current_time();
	i = -1;
	while (++i < data->num_philos)
	{
		if (pthread_create(&data->philosophers[i].thread, NULL,
				philosopher_routine, &data->philosophers[i]) != 0)
		{
			data->simulation_stop = true;
			return (clear_everything(data), false);
		}
	}
	if (pthread_create(&data->monitor, NULL, monitor_routine, data) != 0)
	{
		data->simulation_stop = true;
		return (clear_everything(data), false);
	}
	i = -1;
	while (++i < data->num_philos)
		pthread_join(data->philosophers[i].thread, NULL);
	pthread_join(data->monitor, NULL);
	return (true);
}
