/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtskitis <gtskitis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 23:34:55 by gtskitis          #+#    #+#             */
/*   Updated: 2024/04/23 23:38:26 by gtskitis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>

# define MAX_PHILOS 200

# define MAX_INT 2147483647

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	eating;
	int				row;
	int				times_ate;
	int				fork[2];
	long long int	last_time_ate;
	struct s_data	*data;
}		t_philo;

typedef struct s_data
{
	pthread_t		stopper;
	int				philos_count;
	int				time_eat;
	int				time_sleep;
	int				time_death;
	int				max_eats;
	long long int	starting_time;
	bool			should_stop;
	bool			philo_died;
	bool			max_ate;
	pthread_mutex_t	stop;
	pthread_mutex_t	print;
	pthread_mutex_t	*fork;
	t_philo			**philo;
}		t_data;

t_data			*init_data(int argc, char **argv);
long long int	cal_time(void);
void			print_message(t_data *data, int i, char *msg);
void			start_sleeping(t_data *data, long long int sleep_time);
void			sim_start_delay(long long int starting_time);
void			*routine_stopper(void *data);
void			*free_data(t_data *data);
void			destroy_mutexes(t_data *data);
void			*routine(void *data);
void			stop_exec(t_data	*data);
bool			free_and_exit(t_data *data);
bool			start_exec(t_data *data);
bool			wrong_input(char **argv);
bool			loop_stopped(t_data *data);
int				ft_atoi(char *str);
int				error_failure(char *str, char *details, t_data *data);

#endif
