/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtskitis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 23:35:12 by gtskitis          #+#    #+#             */
/*   Updated: 2024/04/23 23:35:13 by gtskitis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	stop_exec(t_data	*data)
{
	int	i;

	i = 0;
	while (i < data->philos_count)
	{
		pthread_join(data->philo[i]->thread, NULL);
		i++;
	}
	if (data->philos_count > 1)
		pthread_join(data->stopper, NULL);
	destroy_mutexes(data);
	free_data(data);
}

void	*free_data(t_data *data)
{
	int	i;

	if (!data)
		return (NULL);
	if (data->fork != NULL)
		free(data->fork);
	if (data->philo != NULL)
	{
		i = 0;
		while (i < data->philos_count)
		{
			if (data->philo[i] != NULL)
				free(data->philo[i]);
			i++;
		}
		free(data->philo);
	}
	free(data);
	return (NULL);
}

void	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_count)
	{
		pthread_mutex_destroy(&data->fork[i]);
		pthread_mutex_destroy(&data->philo[i]->eating);
		i++;
	}
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->stop);
}
