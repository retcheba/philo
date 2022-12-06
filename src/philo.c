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

static void	init_mutex(t_philo *philo, t_struct	*structs)
{
	size_t		i;

	structs->forks = malloc(sizeof(pthread_mutex_t) * philo->number_of_philosophers);
	i = 0;
	while (i < philo->number_of_philosophers)
	{
		pthread_mutex_init(&structs->forks[i], NULL);
		pthread_mutex_init(&structs->threads[i].is_eating, NULL);
		i++;
	}
}

static void	destroy_mutex(t_philo *philo, t_struct	*structs)
{
	size_t		i;

	i = 0;
	while (i < philo->number_of_philosophers)
	{
		pthread_mutex_destroy(&structs->forks[i]);
		pthread_mutex_destroy(&structs->threads[i].is_eating);
		i++;
	}
}

void	*routine(void *arg)
{
	t_thread *thread;

	thread = (t_thread *)arg;
	if (pthread_mutex_lock(thread->left_fork) == 0)
		printf("Philo %d takes his fork\n", thread->philo);
	if (pthread_mutex_lock(thread->right_fork) == 0)
		printf("Philo %d takes fork of philo %d\n", thread->philo, thread->philo + 1);
	if (pthread_mutex_lock(&thread->is_eating) == 0)
		printf("Philo %d is eating\n", thread->philo);
	pthread_mutex_unlock(thread->left_fork);
	pthread_mutex_unlock(thread->right_fork);
	pthread_mutex_unlock(&thread->is_eating);
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
	init_mutex(philo, &structs);
	i = 0;
	while (i < philo->number_of_philosophers)
	{
		structs.threads[i].philo = i;
		structs.threads[i].left_fork = &structs.forks[i];
		if (i + 1 == philo->number_of_philosophers)
			structs.threads[i].right_fork = &structs.forks[0];
		else
			structs.threads[i].right_fork = &structs.forks[i + 1];
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
		i++;
	}
	destroy_mutex(philo, &structs);
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
