/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:57:00 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/29 18:26:40 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	meals_checker(struct s_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex.done_eating_mutex);
	if (philo->meals == philo->data->num_of_eat)
		philo->done_eating = true;
	pthread_mutex_unlock(&philo->data->mutex.done_eating_mutex);
}

bool	philo_eat(struct s_philo *philo)
{
	if (philo->data->dead == true)
		return (false);
	if (pick_forks(philo) == false)
		return (false);
	print_state(philo, 2);
	philo->last_time_eat = get_time();
	ft_usleep(philo->data->time_to_eat);
	leave_forks(philo);
	pthread_mutex_lock(&philo->data->mutex.done_eating_mutex);
	philo->meals++;
	pthread_mutex_unlock(&philo->data->mutex.done_eating_mutex);
	meals_checker(philo);
	return (true);
}

void	*philo_routine(struct s_philo *philo)
{
	if (philo_eat(philo) == false)
		return (NULL);
	pthread_mutex_lock(&(philo->data->mutex.dead_mutex));
	if (everything_is_ok(philo) == true)
	{
		pthread_mutex_unlock(&(philo->data->mutex.dead_mutex));
		return (NULL);
	}
	pthread_mutex_unlock(&(philo->data->mutex.dead_mutex));
	print_state(philo, 3);
	ft_usleep(philo->data->time_to_sleep);
	if (philo->data->dead == true)
		return (NULL);
	print_state(philo, 4);
	return (philo);
}

void	*call_routine(struct s_philo *philo)
{
	pthread_mutex_lock(&(philo->data->mutex.dead_mutex));
	while (philo->data->dead == false && philo->done_eating == false)
	{
		pthread_mutex_unlock(&(philo->data->mutex.dead_mutex));
		if (philo_routine(philo) == NULL)
			return (NULL);
		pthread_mutex_lock(&(philo->data->mutex.dead_mutex));
	}
	pthread_mutex_unlock(&(philo->data->mutex.dead_mutex));
	return (NULL);
}

void	*life_cycle(void *philo_ptr)
{
	struct s_philo	*philo;

	philo = (struct s_philo *)philo_ptr;
	pthread_mutex_lock(&(philo->data->mutex.start_mutex));
	while (philo->data->start == false)
	{
		pthread_mutex_unlock(&(philo->data->mutex.start_mutex));
		usleep(1);
		pthread_mutex_lock(&(philo->data->mutex.start_mutex));
	}
	pthread_mutex_unlock(&(philo->data->mutex.start_mutex));
	pthread_mutex_lock(&(philo->data->mutex.dead_mutex));
	philo->last_time_eat = get_time();
	pthread_mutex_unlock(&(philo->data->mutex.dead_mutex));
	if (philo->id % 2 != 0)
		ft_usleep(philo->data->time_to_eat);
	call_routine(philo);
	return (NULL);
}
