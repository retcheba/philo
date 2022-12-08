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

void	print_status(t_thread *thread, char	*status, int color)
{
	long long	time;

	if (!is_a_dead_philo(thread))
	{
		time = get_time() - thread->philo_struct->start_time;
		if (color == 92)
		{
			if (time - thread->last_meal > thread->philo_struct->time_to_die)
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
