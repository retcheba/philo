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
}

void	print_status(t_thread *thread, char	*status)
{
	if (pthread_mutex_lock(&thread->philo_struct->printf) == 0)
		printf("Philo %d %s\n", thread->philo, status);
	pthread_mutex_unlock(&thread->philo_struct->printf);
}
