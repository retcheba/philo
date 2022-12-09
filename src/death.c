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

static int	is_to_last(t_thread *thread, long long *time)
{
	pthread_mutex_lock(&thread->philo_struct->to_die_time);
	pthread_mutex_lock(&thread->meal_last);
	if (*time - thread->last_meal > thread->philo_struct->time_to_die)
	{
		pthread_mutex_unlock(&thread->meal_last);
		pthread_mutex_unlock(&thread->philo_struct->to_die_time);
		return (1);
	}
	pthread_mutex_unlock(&thread->meal_last);
	pthread_mutex_unlock(&thread->philo_struct->to_die_time);
	return (0);
}

void	*check_death(void *arg)
{
	int			i;
	long long	time;
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (1 == 1)
	{
		i = 0;
		while (i < philo->number_of_philosophers)
		{
			time = 0;
			set_time(&philo->threads[i], &time);
			if (is_to_last(&philo->threads[i], &time))
			{
				set_death(&philo->threads[i], time);
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}

int	is_a_dead_philo(t_thread *thread)
{
	pthread_mutex_lock(&thread->philo_struct->philo_death);
	if (thread->philo_struct->death == 1)
	{
		pthread_mutex_unlock(&thread->philo_struct->philo_death);
		return (1);
	}
	pthread_mutex_unlock(&thread->philo_struct->philo_death);
	return (0);
}

void	set_death(t_thread *thread, long long time)
{
	pthread_mutex_lock(&thread->philo_struct->philo_death);
		thread->philo_struct->death = 1;
		thread->philo_struct->death_time = time;
		thread->philo_struct->death_philo = thread->philo;
	pthread_mutex_unlock(&thread->philo_struct->philo_death);
}

void	print_death(t_philo *philo)
{
	if (philo->death == 1
		&& !(philo->number_of_philo_fat >= philo->number_of_philosophers))
		printf("\033[91m%lld %d died\n\033[0m", philo->death_time, \
			philo->death_philo);
}
