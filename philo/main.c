/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:56:40 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/29 18:17:10 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	pick_forks(struct s_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex.forks[philo->left_fork]);
	print_state(philo, 1);
	if (philo->data->num_of_philo == 1)
	{
		ft_usleep(philo->data->time_to_die);
		pthread_mutex_unlock(&philo->data->mutex.forks[philo->left_fork]);
		return (false);
	}
	pthread_mutex_lock(&philo->data->mutex.forks[philo->right_fork]);
	print_state(philo, 1);
	return (true);
}

void	leave_forks(struct s_philo *philo)
{
	pthread_mutex_unlock(&philo->data->mutex.forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->mutex.forks[philo->right_fork]);
}

bool	philos_all_done_eating(struct s_data *data, int num_of_philos)
{
	int	i;

	i = 0;
	while (i < num_of_philos)
	{
		if (data->philos[i].done_eating == false)
			return (false);
		i++;
	}
	return (true);
}

void	monitoring(struct s_data *data)
{
	struct s_philo	*philo;
	int				i;

	philo = data->philos;
	while (true)
	{
		i = 0;
		while (i < data->num_of_philo && data->dead == false)
		{
			pthread_mutex_lock(&(data->mutex.dead_mutex));
			philo[i].expected_death_time = get_time() - philo[i].last_time_eat;
			pthread_mutex_unlock(&(data->mutex.dead_mutex));
			if (philo[i].expected_death_time > data->time_to_die - 1)
			{
				pthread_mutex_lock(&(data->mutex.dead_mutex));
				print_state(philo, 5);
				data->dead = true;
				pthread_mutex_unlock(&(data->mutex.dead_mutex));
				return ;
			}
			if (philos_all_done_eating(data, data->num_of_philo))
				return ;
			i++;
		}
	}
}

int	main(int ac, char **av)
{
	struct s_data	data;

	if (input_parsing(ac, av) == true)
	{
		if (init_data(&data, ac, av) == true)
		{
			if (init_mutex(&data) == true)
			{
				if (init_philos(&data) == true)
				{
					if (init_threads(&data) == true)
						monitoring(&data);
				}
				philos_destroy(&data);
			}
			mutex_destroy(&data);
		}
		data_destroy(&data);
	}
	return (0);
}
