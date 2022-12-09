/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 12:52:04 by retcheba          #+#    #+#             */
/*   Updated: 2022/12/04 12:52:07 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_atoi(const char *num)
{
	int	result;
	int	i;

	result = 0;
	i = 0;
	if (num[i] == '\0')
		return (0);
	while (num[i] >= '0' && num[i] <= '9' && num[i])
		i++;
	if (num[i] != '\0')
		return (0);
	i = 0;
	while (num[i] >= '0' && num[i] <= '9' && num[i])
	{
		result *= 10;
		result += num[i] - '0';
		i++;
	}
	return (result);
}

void	init_mutex(t_philo *philo)
{
	int	i;

	philo->forks = malloc(sizeof(pthread_mutex_t) \
		* philo->number_of_philosophers);
	i = 0;
	while (i < philo->number_of_philosophers)
	{
		pthread_mutex_init(&philo->forks[i], NULL);
		pthread_mutex_init(&philo->threads[i].meal_last, NULL);
		i++;
	}
	pthread_mutex_init(&philo->printf, NULL);
	pthread_mutex_init(&philo->philo_fat, NULL);
	pthread_mutex_init(&philo->philo_death, NULL);
	pthread_mutex_init(&philo->time_start, NULL);
	pthread_mutex_init(&philo->to_die_time, NULL);
}

void	destroy_mutex(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->number_of_philosophers)
	{
		pthread_mutex_destroy(&philo->forks[i]);
		pthread_mutex_destroy(&philo->threads[i].meal_last);
		i++;
	}
	free(philo->forks);
	pthread_mutex_destroy(&philo->printf);
	pthread_mutex_destroy(&philo->philo_fat);
	pthread_mutex_destroy(&philo->philo_death);
	pthread_mutex_destroy(&philo->time_start);
	pthread_mutex_destroy(&philo->to_die_time);
}

long long	get_time(void)
{
	struct timeval	tv;
	long long		time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}

void	set_time(t_thread *thread, long long *time)
{
	if (pthread_mutex_lock(&thread->philo_struct->time_start) == 0)
		*time = get_time() - thread->philo_struct->start_time;
	pthread_mutex_unlock(&thread->philo_struct->time_start);
}
