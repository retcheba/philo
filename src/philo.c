/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 13:55:10 by retcheba          #+#    #+#             */
/*   Updated: 2022/12/04 13:55:14 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*routine(void *arg)
{
	t_thread *thread;

	thread = (t_thread *)arg;
	for (int i = 0; i < 1000000; i++)
	{
		pthread_mutex_lock(&thread->mutex);
		thread->mails++;
		pthread_mutex_unlock(&thread->mutex);
	}
	return (NULL);
}

void	init_threads(t_philo *philo)
{
	pthread_t	t1, t2, t3, t4;
	t_thread	thread;

	(void)philo;
	thread.mails = 0;
	pthread_mutex_init(&thread.mutex, NULL);
	if (pthread_create(&t1, NULL, &routine, &thread) != 0)
		return ;
	if (pthread_create(&t2, NULL, &routine, &thread) != 0)
		return ;
	if (pthread_create(&t3, NULL, &routine, &thread) != 0)
		return ;
	if (pthread_create(&t4, NULL, &routine, &thread) != 0)
		return ;
	if (pthread_join(t1, NULL) != 0)
		return ;
	if (pthread_join(t2, NULL) != 0)
		return ;
	if (pthread_join(t3, NULL) != 0)
		return ;
	if (pthread_join(t4, NULL) != 0)
		return ;
	pthread_mutex_destroy(&thread.mutex);
	printf("Number of mails=%d\n", thread.mails);
}

void	ft_philo(t_philo *philo)
{
	printf("number_of_philosophers=%ld\n", philo->number_of_philosophers);
	printf("time_to_die=%ld\n", philo->time_to_die);
	printf("time_to_eat=%ld\n", philo->time_to_eat);
	printf("time_to_sleep=%ld\n", philo->time_to_sleep);
	printf("number_of_times_each_philosopher_must_eat=%ld\n\n", \
		philo->number_of_times_each_philosopher_must_eat);
	init_threads(philo);
}
