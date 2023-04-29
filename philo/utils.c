/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:57:00 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/29 18:27:14 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*get_string(int index)
{
	if (index == 1)
		return ("has taken a fork");
	else if (index == 2)
		return ("is eating");
	else if (index == 3)
		return ("is sleeping");
	else if (index == 4)
		return ("is thinking");
	else if (index == 5)
		return ("died");
	return ("error");
}

long	get_time(void)
{
	struct timeval	timeval;
	long			ms;

	gettimeofday(&timeval, NULL);
	ms = timeval.tv_sec * 1000;
	ms += timeval.tv_usec / 1000;
	return (ms);
}

void	print_state(struct s_philo *philo, int string_index)
{
	char	*str;

	str = get_string(string_index);
	pthread_mutex_lock(&philo->data->mutex.write_mutex);
	if (philo->data->dead == true)
	{
		pthread_mutex_unlock(&philo->data->mutex.write_mutex);
		return ;
	}
	printf("%lld %d %s\n", get_time() - philo->data->start_time,
		philo->id, str);
	pthread_mutex_unlock(&philo->data->mutex.write_mutex);
	return ;
}

void	ft_usleep(long time)
{
	long	starting_time;

	starting_time = get_time();
	while (starting_time + time > get_time())
		usleep(200);
	return ;
}

bool	everything_is_ok(struct s_philo *philo)
{
	return (philo->done_eating == true
		|| philo->data->num_of_philo == 1
		|| philo->data->dead == true);
}
