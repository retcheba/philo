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
		i++;
	}
	pthread_mutex_init(&philo->printf, NULL);
	pthread_mutex_init(&philo->philo_fat, NULL);
	pthread_mutex_init(&philo->philo_death, NULL);
}

void	destroy_mutex(t_philo *philo)
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
	pthread_mutex_destroy(&philo->philo_fat);
	pthread_mutex_destroy(&philo->philo_death);
}

void	print_status(t_thread *thread, char	*status, int color)
{
	long long	time;

	if (thread->philo_struct->death != 1)
	{
		time = get_time() - thread->philo_struct->start_time;
		if (color == 92)
		{
			if (time - thread->last_meal > thread->philo_struct->time_to_die)
			{
				print_death(thread, time);
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

long long	get_time(void)
{
	struct timeval	tv;
	long long		time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}
