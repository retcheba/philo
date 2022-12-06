/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 12:36:52 by retcheba          #+#    #+#             */
/*   Updated: 2022/12/04 12:36:54 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>

typedef struct s_thread	t_thread;
typedef struct s_philo	t_philo;

struct s_thread
{
	int				philo;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_philo			*philo_struct;
};

struct s_philo
{
	size_t			number_of_philosophers;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			number_of_times_each_philosopher_must_eat;
	t_thread		*threads;
	pthread_mutex_t	*forks;
	pthread_mutex_t	printf;
};

size_t	ft_atoi(const char *num);
void	ft_philo(t_philo *philo);

#endif