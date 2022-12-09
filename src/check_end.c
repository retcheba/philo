/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:46:49 by retcheba          #+#    #+#             */
/*   Updated: 2022/12/09 15:47:53 by retcheba         ###   ########.fr       */
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

static int	all_the_philo_are_fat(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_fat);
	if (philo->number_of_philo_fat >= philo->number_of_philosophers)
	{
		pthread_mutex_unlock(&philo->philo_fat);
		return (1);
	}
	pthread_mutex_unlock(&philo->philo_fat);
	return (0);
}

void	*check_end(void *arg)
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
			if (is_to_last(&philo->threads[i], &time)
				|| all_the_philo_are_fat(philo))
			{
				set_death(&philo->threads[i], time);
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}
