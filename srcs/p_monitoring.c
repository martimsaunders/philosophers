/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_monitoring.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:34:25 by mprazere          #+#    #+#             */
/*   Updated: 2025/07/09 11:20:40 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	kill_philo(t_data *data, int i)
{
	pthread_mutex_unlock(&data->meal_mutex);
	print_action(&data->philosophers[i], DIED);
	pthread_mutex_lock(&data->death_mutex);
	data->simulation_stop = true;
	pthread_mutex_unlock(&data->death_mutex);
}

static void	finish_simulation(t_data *data)
{
	pthread_mutex_lock(&data->death_mutex);
	data->simulation_stop = true;
	pthread_mutex_unlock(&data->death_mutex);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;
	bool	full;

	data = (t_data *)arg;
	while (data->simulation_stop == false)
	{
		full = true;
		i = -1;
		while (++i < data->num_philos && data->simulation_stop == false)
		{
			pthread_mutex_lock(&data->meal_mutex);
			if (get_current_time()
				- data->philosophers[i].last_meal_time > data->time_to_die)
				return (kill_philo(data, i), NULL);
			if (data->meals_to_eat > 0 && data->philosophers[i].full == false)
				full = false;
			pthread_mutex_unlock(&data->meal_mutex);
		}
		if (data->meals_to_eat > 0 && full == true)
			return (finish_simulation(data), NULL);
		usleep(1000);
	}
	return (NULL);
}
