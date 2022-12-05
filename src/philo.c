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
	pthread_mutex_lock(&thread->mutex);
	printf("I am philo number %d\n", thread->philo);
	pthread_mutex_unlock(&thread->mutex);
	return (NULL);
}

void	init_threads(t_philo *philo)
{
	pthread_t	*th;
	t_struct	structs;
	size_t		i;

	(void)philo;
	th = malloc(sizeof(pthread_t) * philo->number_of_philosophers);
	structs.threads = malloc(sizeof(t_thread) * philo->number_of_philosophers);
	i = 0;
	while (i < philo->number_of_philosophers)
	{
		pthread_mutex_init(&structs.threads[i].mutex, NULL);
		structs.threads[i].philo = i;
		if (pthread_create(&th[i], NULL, &routine, &structs.threads[i]) != 0)
		{
			perror("Failed to create thread\n");
			return ;
		}
		i++;
	}
	i = 0;
	while (i < philo->number_of_philosophers)
	{
		if (pthread_join(th[i], NULL) != 0)
			return ;
		pthread_mutex_destroy(&structs.threads[i].mutex);
		i++;
	}
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
