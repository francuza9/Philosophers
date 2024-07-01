/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtskitis <gtskitis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 23:35:26 by gtskitis          #+#    #+#             */
/*   Updated: 2024/04/23 23:36:43 by gtskitis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

pthread_mutex_t	*mutex_forks(t_data *data)
{
	pthread_mutex_t	*fork;
	int				i;

	i = 0;
	fork = malloc(sizeof(pthread_mutex_t) * data->philos_count);
	if (!fork)
		return (NULL);
	while (i < data->philos_count)
	{
		if (pthread_mutex_init(&fork[i], 0))
			return (NULL);
		i++;
	}
	return (fork);
}

void	assign_forks(t_philo *philo)
{
	philo->fork[0] = philo->row;
	philo->fork[1] = (philo->row + 1) % philo->data->philos_count;
	if (philo->row % 2)
	{
		philo->fork[0] = (philo->row + 1) % philo->data->philos_count;
		philo->fork[1] = philo->row;
	}
}

t_philo	**philo_init(t_data *data)
{
	t_philo			**philo;
	int				i;

	philo = malloc(sizeof(t_philo) * data->philos_count);
	if (!philo)
		return (NULL);
	i = 0;
	while (i < data->philos_count)
	{
		philo[i] = malloc(sizeof(t_philo));
		if (!philo[i] || pthread_mutex_init(&philo[i]->eating, NULL))
		{
			free_data(data);
			return (NULL);
		}
		philo[i]->data = data;
		philo[i]->row = i;
		philo[i]->times_ate = 0;
		philo[i]->last_time_ate = 0;
		assign_forks(philo[i]);
		i++;
	}
	return (philo);
}

bool	mutex_init(t_data *data)
{
	data->fork = mutex_forks(data);
	if (!data->fork \
	|| pthread_mutex_init(&data->stop, 0) \
	|| pthread_mutex_init(&data->print, 0))
	{
		free_data(data);
		return (false);
	}
	return (true);
}

t_data	*init_data(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data) * 1);
	if (!data)
		return (NULL);
	data->philos_count = ft_atoi(argv[0]);
	data->time_death = ft_atoi(argv[1]);
	data->time_eat = ft_atoi(argv[2]);
	data->time_sleep = ft_atoi(argv[3]);
	data->philo_died = false;
	data->max_eats = -1;
	if (argc == 6)
		data->max_eats = ft_atoi(argv[4]);
	data->philo = philo_init(data);
	if (!data->philo)
		return (NULL);
	if (!mutex_init(data))
		return (NULL);
	data->should_stop = false;
	return (data);
}
