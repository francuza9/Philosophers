/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtskitis <gtskitis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 23:35:05 by gtskitis          #+#    #+#             */
/*   Updated: 2024/04/23 23:48:42 by gtskitis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	start_eating(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&philo->data->fork[philo->fork[0]]);
	print_message(data, philo->row, "has taken a fork\n");
	pthread_mutex_lock(&philo->data->fork[philo->fork[1]]);
	print_message(data, philo->row, "has taken a fork\n");
	print_message(data, philo->row, "is eating\n");
	pthread_mutex_lock(&philo->eating);
	philo->last_time_ate = cal_time();
	pthread_mutex_unlock(&philo->eating);
	start_sleeping(philo->data, philo->data->time_eat);
	if (loop_stopped(philo->data) == false)
	{
		pthread_mutex_lock(&philo->eating);
		philo->times_ate++;
		pthread_mutex_unlock(&philo->eating);
	}
	print_message(data, philo->row, "is sleeping\n");
	pthread_mutex_unlock(&philo->data->fork[philo->fork[1]]);
	pthread_mutex_unlock(&philo->data->fork[philo->fork[0]]);
	start_sleeping(philo->data, philo->data->time_sleep);
}

void	think_routine(t_philo *philo, bool print)
{
	long long int	wait_time;

	pthread_mutex_lock(&philo->eating);
	wait_time = (philo->data->time_death \
	- (cal_time() - philo->last_time_ate) \
	- philo->data->time_eat) / 2;
	pthread_mutex_unlock(&philo->eating);
	if (wait_time < 0)
		wait_time = 0;
	if (wait_time == 0)
		wait_time = 1;
	if (wait_time > 600)
		wait_time = 200;
	if (print == true)
	{
		print_message (philo->data, philo->row, "is thinking\n");
		return ;
	}
	start_sleeping(philo->data, wait_time);
}

void	*single_philo(t_philo *philo)
{
	printf("0 1 has taken a fork\n");
	usleep(philo->data->time_death * 1000);
	printf("%d 1 has died\n", philo->data->time_death);
	return (NULL);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->data->max_eats == 0)
		return (NULL);
	pthread_mutex_lock(&philo->eating);
	philo->last_time_ate = philo->data->starting_time;
	pthread_mutex_unlock(&philo->eating);
	while (cal_time() < philo->data->starting_time)
		continue ;
	if (philo->data->time_death == 0)
		return (NULL);
	if (philo->data->philos_count == 1)
		return (single_philo(philo));
	else if (philo->row % 2)
		think_routine(philo, false);
	while (!loop_stopped(philo->data))
	{
		if (philo->times_ate != philo->data->max_eats)
		{
			start_eating(philo);
			think_routine(philo, true);
		}
	}
	return (NULL);
}

bool	start_exec(t_data *data)
{
	int	i;

	data->starting_time = cal_time() + (data->philos_count * 20);
	i = -1;
	while (++i < data->philos_count)
	{
		if (pthread_create(&data->philo[i]->thread, NULL,
				&routine, data->philo[i]) != 0)
			return (true);
	}
	if (data->philos_count > 1)
	{
		if (pthread_create(&data->stopper, NULL,
				&routine_stopper, data) != 0)
			return (true);
	}
	return (false);
}
