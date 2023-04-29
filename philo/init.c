/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:57:00 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/29 16:07:07 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	init_data(struct s_data *data, int ac, char **av)
{
	if (!data)
		return (false);
	data->num_of_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->num_of_eat = ft_atoi(av[5]);
	else
		data->num_of_eat = -4242;
	data->dead = false;
	data->start = false;
	data->start_time = get_time();
	return (true);
}

bool	init_mutex(struct s_data *data)
{
	int	i;

	i = 0;
	data->mutex.forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philo);
	while (i < data->num_of_philo)
	{
		if (pthread_mutex_init(&data->mutex.forks[i], NULL))
			return (false);
		i++;
	}
	if (pthread_mutex_init(&data->mutex.dead_mutex, NULL))
		return (false);
	if (pthread_mutex_init(&data->mutex.start_mutex, NULL))
		return (false);
	if (pthread_mutex_init(&data->mutex.write_mutex, NULL))
		return (false);
	if (pthread_mutex_init(&data->mutex.done_eating_mutex, NULL))
		return (false);
	if (pthread_mutex_init(&data->mutex.init_mutex, NULL))
		return (false);
	return (true);
}

bool	init_philos(struct s_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(struct s_philo) * data->num_of_philo);
	while (i < data->num_of_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals = 0;
		data->philos[i].data = data;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % data->num_of_philo;
		data->philos[i].data = data;
		data->philos[i].done_eating = false;
		data->philos[i].last_time_eat = get_time();
		i++;
	}
	return (true);
}

bool	init_threads(struct s_data *data)
{
	int	i;

	pthread_mutex_lock(&data->mutex.init_mutex);
	i = 0;
	while (i < data->num_of_philo)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				&life_cycle, &data->philos[i]))
		{
			pthread_mutex_unlock(&data->mutex.init_mutex);
			return (false);
		}
		i++;
	}
	pthread_mutex_unlock(&data->mutex.init_mutex);
	pthread_mutex_lock(&data->mutex.start_mutex);
	data->start = true;
	data->start_time = get_time();
	pthread_mutex_unlock(&data->mutex.start_mutex);
	return (true);
}
