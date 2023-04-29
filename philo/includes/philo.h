/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:57:00 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/29 18:20:44 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

struct s_mutex
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	start_mutex;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	done_eating_mutex;
	pthread_mutex_t	init_mutex;
};

struct s_data
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_eat;
	int				dead;
	bool			start;
	long long		start_time;
	struct s_mutex	mutex;
	struct s_philo	*philos;
};

struct s_philo
{
	int				id;
	int				meals;
	int				left_fork;
	int				right_fork;
	bool			done_eating;
	long long		last_time_eat;
	pthread_t		thread;
	struct s_data	*data;
	long long		expected_death_time;
};

// ft_atoi.c
int		ft_isdigit(int n);
int		ft_atoi(const char *str);
int		error(char *msg);

// parsing.c
bool	check_if_number(char *str);
bool	input_parsing(int ac, char **av);

// init.c
bool	init_data(struct s_data *data, int ac, char **av);
bool	init_mutex(struct s_data *data);
bool	init_philos(struct s_data *data);
bool	init_threads(struct s_data *data);

// destroy.c
void	philos_destroy(struct s_data *data);
void	mutex_destroy(struct s_data *data);
void	data_destroy(struct s_data *data);

// life_cycel.c
void	meals_checker(struct s_philo *philo);
bool	philo_eat(struct s_philo *philo);
void	*philo_routine(struct s_philo *philo);
void	*call_routine(struct s_philo *philo);
void	*life_cycle(void *philo_ptr);

// utils.c
char	*get_string(int index);
long	get_time(void);
void	print_state(struct s_philo *philo, int string_index);
void	ft_usleep(long time);
bool	everything_is_ok(struct s_philo *philo);

// main.c
bool	pick_forks(struct s_philo *philo);
void	leave_forks(struct s_philo *philo);
bool	philos_all_done_eating(struct s_data *data, int num_of_philos);
void	monitoring(struct s_data *data);

#endif