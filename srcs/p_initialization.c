/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_initialization.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:13:27 by mprazere          #+#    #+#             */
/*   Updated: 2025/07/09 11:22:08 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	initialize_data(t_data *data)
{
	int	i;

	i = -1;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (false);
	while (++i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (clear_forks(data, i), false);
	}
	if (pthread_mutex_init(&data->write_mutex, NULL) != 0)
		return (clear_forks(data, i), false);
	if (pthread_mutex_init(&data->meal_mutex, NULL) != 0)
		return (pthread_mutex_destroy(&data->write_mutex), clear_forks(data, i),
			false);
	if (pthread_mutex_init(&data->death_mutex, NULL) != 0)
		return (pthread_mutex_destroy(&data->write_mutex),
			pthread_mutex_destroy(&data->meal_mutex), clear_forks(data, i),
			false);
	data->simulation_stop = false;
	return (true);
}

bool	initialize_philosophers(t_data *data)
{
	int	i;

	data->philosophers = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philosophers)
		return (clear_everything(data), false);
	i = -1;
	while (++i < data->num_philos)
	{
		data->philosophers[i].id = i + 1;
		data->philosophers[i].meals_eaten = 0;
		data->philosophers[i].full = false;
		data->philosophers[i].last_meal_time = get_current_time();
		data->philosophers[i].data = data;
		data->philosophers[i].left_fork = &data->forks[i];
		data->philosophers[i].right_fork = &data->forks[(i + 1)
			% data->num_philos];
	}
	return (true);
}
