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
	if (is_only_one_philo(thread))
		return (NULL);
	if (thread->philo % 2 == 0)
		usleep(5000);
	while (1 == 1)
	{
		print_status(thread, "is thinking", 95);
		pthread_mutex_lock(thread->left_fork);
		print_status(thread, "has taken a fork", 93);
		pthread_mutex_lock(thread->right_fork);
		print_status(thread, "has taken a fork", 93);
		print_status(thread, "is eating", 92);
		usleep(1000 * thread->philo_struct->time_to_eat);
		pthread_mutex_unlock(thread->left_fork);
		pthread_mutex_unlock(thread->right_fork);
		print_status(thread, "is sleeping", 96);
		usleep(1000 * thread->philo_struct->time_to_sleep);
		if (is_a_dead_philo(thread))
			break ;
	}
	return (NULL);
}

static void	check_if_the_philo_is_fat(t_thread	*thread)
{
	thread->i++;
	if (thread->i == thread->philo_struct->number_of_times_each_philo_must_eat)
	{
		pthread_mutex_lock(&thread->philo_struct->philo_fat);
		thread->philo_struct->number_of_philo_fat++;
		pthread_mutex_unlock(&thread->philo_struct->philo_fat);
	}
}

static int	all_the_philo_are_fat(t_thread	*thread)
{
	pthread_mutex_lock(&thread->philo_struct->philo_fat);
	if (thread->philo_struct->number_of_philo_fat >= \
		thread->philo_struct->number_of_philosophers)
	{
		pthread_mutex_unlock(&thread->philo_struct->philo_fat);
		return (1);
	}
	pthread_mutex_unlock(&thread->philo_struct->philo_fat);
	return (0);
}

void	*routine_defined_end(void *arg)
{
	t_thread	*thread;

	thread = (t_thread *)arg;
	if (is_only_one_philo(thread))
		return (NULL);
	if (thread->philo % 2 == 0)
		usleep(5000);
	while (1 == 1)
	{
		print_status(thread, "is thinking", 95);
		pthread_mutex_lock(thread->left_fork);
		print_status(thread, "has taken a fork", 93);
		pthread_mutex_lock(thread->right_fork);
		print_status(thread, "has taken a fork", 93);
		print_status(thread, "is eating", 92);
		usleep(1000 * thread->philo_struct->time_to_eat);
		pthread_mutex_unlock(thread->left_fork);
		pthread_mutex_unlock(thread->right_fork);
		print_status(thread, "is sleeping", 96);
		usleep(1000 * thread->philo_struct->time_to_sleep);
		check_if_the_philo_is_fat(thread);
		if (all_the_philo_are_fat(thread) || is_a_dead_philo(thread))
			break ;
	}
	return (NULL);
}
