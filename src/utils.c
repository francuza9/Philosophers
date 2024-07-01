/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtskitis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 23:35:39 by gtskitis          #+#    #+#             */
/*   Updated: 2024/04/23 23:35:41 by gtskitis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	print_message(t_data *data, int i, char *msg)
{
	pthread_mutex_lock(&data->print);
	if (!data->philo_died)
		printf("%lld %d %s",
			cal_time() - data->starting_time, i + 1, msg);
	if (msg[0] == 'd')
		data->philo_died = true;
	pthread_mutex_unlock(&data->print);
}

long long int	cal_time(void)
{
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	start_sleeping(t_data *data, long long int sleep_time)
{
	long long int	wake_up;

	wake_up = cal_time() + sleep_time;
	while (cal_time() < wake_up)
	{
		if (loop_stopped(data))
			break ;
		usleep(100);
	}
}
