/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   force_stop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtskitis <gtskitis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 23:35:19 by gtskitis          #+#    #+#             */
/*   Updated: 2024/04/23 23:36:25 by gtskitis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	change_stop(t_data *data, bool flag)
{
	pthread_mutex_lock(&data->stop);
	data->should_stop = flag;
	pthread_mutex_unlock(&data->stop);
}

bool	loop_stopped(t_data *data)
{
	bool	flag;

	flag = false;
	pthread_mutex_lock(&data->stop);
	if (data->should_stop == true)
		flag = true;
	pthread_mutex_unlock(&data->stop);
	return (flag);
}

bool	stop_philo(t_philo *philo)
{
	long long int	time;

	time = cal_time();
	if ((time - philo->last_time_ate) >= philo->data->time_death)
	{
		change_stop(philo->data, true);
		print_message(philo->data, philo->row, "died\n");
		pthread_mutex_unlock(&philo->eating);
		return (true);
	}
	return (false);
}

bool	should_stop(t_data *data)
{
	int		i;
	bool	everyone_ate;

	everyone_ate = true;
	i = 0;
	while (i < data->philos_count)
	{
		pthread_mutex_lock(&data->philo[i]->eating);
		if (stop_philo(data->philo[i]))
			return (true);
		if (data->max_eats != -1)
			if (data->philo[i]->times_ate
				< (int)data->max_eats)
				everyone_ate = false;
		pthread_mutex_unlock(&data->philo[i]->eating);
		i++;
	}
	if (data->max_eats != -1 && everyone_ate == true)
	{
		change_stop(data, true);
		return (true);
	}
	return (false);
}

void	*routine_stopper(void *void_data)
{
	t_data			*data;

	data = (t_data *)void_data;
	if (data->max_eats == 0)
		return (NULL);
	change_stop(data, false);
	while (cal_time() < data->starting_time)
		continue ;
	while (true)
	{
		if (should_stop(data))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
