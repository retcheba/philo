/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:42:32 by retcheba          #+#    #+#             */
/*   Updated: 2022/12/08 17:42:35 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	set_time(t_thread *thread, long long *time)
{
	if (pthread_mutex_lock(&thread->philo_struct->time_start) == 0)
		*time = get_time() - thread->philo_struct->start_time;
	pthread_mutex_unlock(&thread->philo_struct->time_start);
}

static int	is_to_last(t_thread *thread, long long *time)
{
	if (pthread_mutex_lock(&thread->philo_struct->to_die_time) == 0)
	{
		if (*time - thread->last_meal > thread->philo_struct->time_to_die)
		{
			pthread_mutex_unlock(&thread->philo_struct->to_die_time);
			return (1);
		}
	}
	pthread_mutex_unlock(&thread->philo_struct->to_die_time);
	return (0);
}

void	print_status(t_thread *thread, char	*status, int color)
{
	long long	time;

	if (!is_a_dead_philo(thread))
	{
		set_time(thread, &time);
		if (color == 92)
		{
			if (is_to_last(thread, &time))
			{
				set_death(thread, time);
				return ;
			}
			thread->last_meal = time;
		}
		if (pthread_mutex_lock(&thread->philo_struct->printf) == 0)
			printf("\033[%dm%lld %d %s\n\033[0m", color, time, thread->philo, \
				status);
		pthread_mutex_unlock(&thread->philo_struct->printf);
	}
}
