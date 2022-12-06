/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 17:49:47 by retcheba          #+#    #+#             */
/*   Updated: 2022/12/06 17:49:48 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*routine_endless(void *arg)
{
	t_thread	*thread;

	thread = (t_thread *)arg;
	while (1 == 1)
	{
		print_status(thread, "is thinking");
		if (pthread_mutex_lock(thread->left_fork) == 0)
			print_status(thread, "has taken a fork");
		if (pthread_mutex_lock(thread->right_fork) == 0)
			print_status(thread, "has taken a fork");
		print_status(thread, "is eating");
		usleep(1000 * thread->philo_struct->time_to_eat);
		pthread_mutex_unlock(thread->left_fork);
		pthread_mutex_unlock(thread->right_fork);
		print_status(thread, "is sleeping");
		usleep(1000 * thread->philo_struct->time_to_sleep);
	}
	return (NULL);
}

void	*routine_defined_end(void *arg)
{
	t_thread	*thread;
	int			i;

	thread = (t_thread *)arg;
	i = 0;
	while (i < thread->philo_struct->number_of_times_each_philosopher_must_eat)
	{
		print_status(thread, "is thinking");
		if (pthread_mutex_lock(thread->left_fork) == 0)
			print_status(thread, "has taken a fork");
		if (pthread_mutex_lock(thread->right_fork) == 0)
			print_status(thread, "has taken a fork");
		print_status(thread, "is eating");
		usleep(1000 * thread->philo_struct->time_to_eat);
		pthread_mutex_unlock(thread->left_fork);
		pthread_mutex_unlock(thread->right_fork);
		print_status(thread, "is sleeping");
		usleep(1000 * thread->philo_struct->time_to_sleep);
		i++;
	}
	return (NULL);
}
