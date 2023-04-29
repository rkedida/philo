/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:57:00 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/29 13:31:35 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philos_destroy(struct s_data *data)
{
	int				i;
	struct s_philo	*philo;

	i = 0;
	philo = data->philos;
	if (philo == NULL)
		return ;
	while (i < philo->data->num_of_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
}

void	mutex_destroy(struct s_data *data)
{
	if (data->mutex.forks != NULL)
		free(data->mutex.forks);
	pthread_mutex_destroy(&data->mutex.dead_mutex);
	pthread_mutex_destroy(&data->mutex.start_mutex);
	pthread_mutex_destroy(&data->mutex.write_mutex);
	pthread_mutex_destroy(&data->mutex.done_eating_mutex);
}

void	data_destroy(struct s_data *data)
{
	free(data->philos);
}
