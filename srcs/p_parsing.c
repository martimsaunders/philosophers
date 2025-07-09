/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_parsing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:21:22 by mprazere          #+#    #+#             */
/*   Updated: 2025/07/09 11:21:31 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_string(char *s1)
{
	int	i;

	i = 0;
	if (!*s1)
		return (true);
	while (s1[i])
	{
		while ((s1[i] >= 9 && s1[i] <= 13) || s1[i] == 32)
			i++;
		if (s1[i] == '-')
			return (printf("Invalid negative integer"), false);
		if (s1[i] == '+')
			if (s1[++i] == '+')
				return (printf("Invalid double sign integer"), false);
		while (s1[i] >= '0' && s1[i] <= '9')
			i++;
		if (s1[i] && s1[i] != ' ' && (s1[i] < 9 || s1[i] > 13))
			return (printf("Only numbers are allowed"), false);
	}
	return (true);
}

bool	str_prot(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (check_string(argv[i]) == false)
			return (printf(" at %s\n", argv[i]), false);
		i++;
	}
	return (true);
}

bool	parsing(int argc)
{
	if (argc != 5 && argc != 6)
		return (printf(COMMAND_LINE), false);
	return (true);
}

bool	check_zero_values(int argc, char **argv, t_data *data)
{
	long	value;
	int		i;

	i = 0;
	while (++i < argc)
	{
		value = ft_atol(argv[i]);
		if (value > INT_MAX)
			return (printf("Arg: %s reaches INT MAX\n", argv[i]), false);
		if (value <= 0)
			return (printf("Arg: %s Must be positive\n", argv[i]), false);
		if (i == 1)
			data->num_philos = value;
		else if (i == 2)
			data->time_to_die = value;
		else if (i == 3)
			data->time_to_eat = value;
		else if (i == 4)
			data->time_to_sleep = value;
		else if (i == 5)
			data->meals_to_eat = value;
	}
	return (true);
}
