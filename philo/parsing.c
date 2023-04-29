/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:13:07 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/29 17:35:22 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_if_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	input_parsing(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac < 5 || ac > 6)
	{
		printf("Error: Wrong number of arguments\nUsage: ./philo num_of_philo \
time_to_die time_to_eat time_to_sleep [num_of_eat]\n");
		return (0);
	}
	while (av[i])
	{
		if (!check_if_number(av[i]))
			printf("Error: Wrong argument, nummeric arguments required.\n");
		i++;
	}
	return (true);
}
