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

static void	set_last_meal(t_thread *thread, long long time)
{
	pthread_mutex_lock(&thread->meal_last);
		thread->last_meal = time;
	pthread_mutex_unlock(&thread->meal_last);
}

void	print_status(t_thread *thread, char	*status, int color)
{
	long long	time;

	if (!is_a_dead_philo(thread))
	{
		time = 0;
		set_time(thread, &time);
		if (color == 92)
			set_last_meal(thread, time);
		pthread_mutex_lock(&thread->philo_struct->printf);
		printf("\033[%dm%lld %d %s\n\033[0m", color, time, thread->philo, \
			status);
		pthread_mutex_unlock(&thread->philo_struct->printf);
	}
}
