/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:21:54 by retcheba          #+#    #+#             */
/*   Updated: 2022/12/08 16:21:58 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	is_a_dead_philo(t_thread *thread)
{
	if (pthread_mutex_lock(&thread->philo_struct->philo_death) == 0)
	{
		if (thread->philo_struct->death == 1)
		{
			pthread_mutex_unlock(&thread->philo_struct->philo_death);
			return (1);
		}
	}
	pthread_mutex_unlock(&thread->philo_struct->philo_death);
	return (0);
}

int	is_only_one_philo(t_thread *thread)
{
	if (thread->philo_struct->number_of_philosophers < 2)
	{
		print_death(thread, get_time() - thread->philo_struct->start_time);
		pthread_mutex_unlock(thread->left_fork);
		return (1);
	}
	return (0);
}

void	print_death(t_thread *thread, long long time)
{
	if (pthread_mutex_lock(&thread->philo_struct->philo_death) == 0)
		thread->philo_struct->death = 1;
	pthread_mutex_unlock(&thread->philo_struct->philo_death);
	if (pthread_mutex_lock(&thread->philo_struct->printf) == 0)
		printf("\033[91m%lld %d died\n\033[0m", time, thread->philo);
	pthread_mutex_unlock(&thread->philo_struct->printf);
}
