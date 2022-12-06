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

static void	init_mutex(t_philo *philo)
{
	int	i;

	philo->forks = malloc(sizeof(pthread_mutex_t) * philo->number_of_philosophers);
	i = 0;
	while (i < philo->number_of_philosophers)
	{
		pthread_mutex_init(&philo->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&philo->printf, NULL);
}

static void	destroy_mutex(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->number_of_philosophers)
	{
		pthread_mutex_destroy(&philo->forks[i]);
		i++;
	}
	free(philo->forks);
	pthread_mutex_destroy(&philo->printf);
}

static void	*routine_endless(void *arg)
{
	t_thread *thread;

	thread = (t_thread *)arg;
	while (1 == 1)
	{
		if (pthread_mutex_lock(&thread->philo_struct->printf) == 0)
			printf("Philo %d is thinking\n", thread->philo);
		pthread_mutex_unlock(&thread->philo_struct->printf);
		if (pthread_mutex_lock(&thread->philo_struct->printf) == 0)
		{
			if (pthread_mutex_lock(thread->left_fork) == 0)
				printf("Philo %d has taken a fork\n", thread->philo);
			if (pthread_mutex_lock(thread->right_fork) == 0)
				printf("Philo %d has taken a fork\n", thread->philo);
			printf("Philo %d is eating\n", thread->philo);
		}
		pthread_mutex_unlock(&thread->philo_struct->printf);
		usleep(1000 * thread->philo_struct->time_to_eat);
		pthread_mutex_unlock(thread->left_fork);
		pthread_mutex_unlock(thread->right_fork);
		if (pthread_mutex_lock(&thread->philo_struct->printf) == 0)
			printf("Philo %d is sleeping\n", thread->philo);
		pthread_mutex_unlock(&thread->philo_struct->printf);
		usleep(1000 * thread->philo_struct->time_to_sleep);
	}
	return (NULL);
}

static void	*routine_defined_end(void *arg)
{
	t_thread	*thread;
	int			i;

	thread = (t_thread *)arg;
	i = 0;
	while (i < thread->philo_struct->number_of_times_each_philosopher_must_eat)
	{
		if (pthread_mutex_lock(&thread->philo_struct->printf) == 0)
			printf("Philo %d is thinking\n", thread->philo);
		pthread_mutex_unlock(&thread->philo_struct->printf);
		if (pthread_mutex_lock(&thread->philo_struct->printf) == 0)
		{
			if (pthread_mutex_lock(thread->left_fork) == 0)
				printf("Philo %d has taken a fork\n", thread->philo);
			if (pthread_mutex_lock(thread->right_fork) == 0)
				printf("Philo %d has taken a fork\n", thread->philo);
			printf("Philo %d is eating\n", thread->philo);
		}
		pthread_mutex_unlock(&thread->philo_struct->printf);
		usleep(1000 * thread->philo_struct->time_to_eat);
		pthread_mutex_unlock(thread->left_fork);
		pthread_mutex_unlock(thread->right_fork);
		if (pthread_mutex_lock(&thread->philo_struct->printf) == 0)
			printf("Philo %d is sleeping\n", thread->philo);
		pthread_mutex_unlock(&thread->philo_struct->printf);
		usleep(1000 * thread->philo_struct->time_to_sleep);
		i++;
	}
	return (NULL);
}

void	init_threads(t_philo *philo)
{
	pthread_t	*th;
	int			i;

	(void)philo;
	th = malloc(sizeof(pthread_t) * philo->number_of_philosophers);
	philo->threads = malloc(sizeof(t_thread) * philo->number_of_philosophers);
	init_mutex(philo);
	i = 0;
	while (i < philo->number_of_philosophers)
	{
		philo->threads[i].philo = i;
		philo->threads[i].left_fork = &philo->forks[i];
		if (i + 1 == philo->number_of_philosophers)
			philo->threads[i].right_fork = &philo->forks[i - 1];
		else
			philo->threads[i].right_fork = &philo->forks[i + 1];
		philo->threads[i].philo_struct = philo;
		if (philo->number_of_times_each_philosopher_must_eat == -1)
		{
			if (pthread_create(&th[i], NULL, &routine_endless, &philo->threads[i]) != 0)
			{
				perror("Failed to create thread\n");
				return ;
			}
		}
		else
		{
			if (pthread_create(&th[i], NULL, &routine_defined_end, &philo->threads[i]) != 0)
			{
				perror("Failed to create thread\n");
				return ;
			}
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
	destroy_mutex(philo);
	free(th);
	free(philo->threads);
}

void	ft_philo(t_philo *philo)
{
	printf("number_of_philosophers=%d\n", philo->number_of_philosophers);
	printf("time_to_die=%d\n", philo->time_to_die);
	printf("time_to_eat=%d\n", philo->time_to_eat);
	printf("time_to_sleep=%d\n", philo->time_to_sleep);
	printf("number_of_times_each_philosopher_must_eat=%d\n\n", \
		philo->number_of_times_each_philosopher_must_eat);
	init_threads(philo);
}
