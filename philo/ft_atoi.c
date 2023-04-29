/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 17:54:04 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/29 13:31:49 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int n)
{
	if (n >= '0' && n <= '9')
		return (n);
	return (0);
}

static int	ft_isspace(char e)
{
	return (e == ' ' || e == '\f' || e == '\r' || e == '\v'
		|| e == '\t' || e == '\n');
}

int	ft_atoi(const char *str)
{
	int		sign;
	long	nb;
	int		index;

		index = 0;
		nb = 0;
		sign = 1;
	while (ft_isspace(str[index]))
		index++;
	if (str[index] == '-' || str[index] == '+')
	{
		if (str[index] == '-')
			sign = -1;
		index++;
	}
	while (str[index] >= '0' && str[index] <= '9')
	{
		nb = nb * 10 + (ft_isdigit(str[index]) - '0');
		if (nb > 2147483647 && sign == 1)
			return (error("Overflow!\n"));
		if (nb > 2147483648 && sign == -1)
			return (error("Overflow\n"));
		index++;
	}
	return (sign * nb);
}

int	error(char *msg)
{
	if (msg)
		printf("Error: %s", msg);
	else
		printf("Error: Wrong number of arguments!\n");
	return (true);
}
