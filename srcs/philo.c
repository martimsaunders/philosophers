/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:14:43 by praders           #+#    #+#             */
/*   Updated: 2025/07/09 11:20:22 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (parsing(argc) == false || str_prot(argc, argv) == false)
		return (1);
	memset(&data, 0, sizeof(t_data));
	if (check_zero_values(argc, argv, &data) == false)
		return (1);
	if (initialize_data(&data) == false)
		return (printf("Error initializing data\n"), 1);
	if (initialize_philosophers(&data) == false)
		return (printf("Error initializing philosophers\n"), 1);
	if (start_simulation(&data) == false)
		return (printf("Error starting simulation\n"), 1);
	clear_everything(&data);
	return (0);
}
