/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:05:11 by mprazere          #+#    #+#             */
/*   Updated: 2025/07/08 16:59:17 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(const char *nptr)
{
	long	result;
	long	signal;

	signal = 1;
	result = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			signal *= -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + (*nptr - '0');
		nptr++;
	}
	return (signal * result);
}

long long get_current_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_action(t_philo *philo, char *msg)
{
	long long	timestamp;

	if (sim_stop(philo->data) == true && strcmp(msg, DIED) != 0)
		return;
	pthread_mutex_lock(&philo->data->write_mutex);
	timestamp = get_current_time() - philo->data->start_time;
	printf("%lld %d %s\n", timestamp, philo->id, msg);
	pthread_mutex_unlock(&philo->data->write_mutex);
}

bool	sim_stop(t_data *data)
{
	bool result;
	
	pthread_mutex_lock(&data->death_mutex);
	result = data->simulation_stop;
	pthread_mutex_unlock(&data->death_mutex);
	return (result);
}