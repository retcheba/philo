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

static void	create_threads(t_philo *philo, pthread_t *th, int i)
{
	if (philo->number_of_times_each_philo_must_eat == -1)
	{
		if (pthread_create(&th[i], NULL, &routine_endless, \
			&philo->threads[i]) != 0)
		{
			printf("Failed to create thread\n");
			return ;
		}
	}
	else
	{
		if (pthread_create(&th[i], NULL, &routine_defined_end, \
			&philo->threads[i]) != 0)
		{
			printf("Failed to create thread\n");
			return ;
		}
	}
}

static void	join_threads(t_philo *philo, pthread_t *th)
{
	int	i;

	i = 0;
	while (i < (philo->number_of_philosophers + 1))
	{
		if (pthread_join(th[i], NULL) != 0)
			return ;
		i++;
	}
}

static void	init_threads(t_philo *philo, int i)
{
	philo->threads[i].philo = i + 1;
	philo->threads[i].i = 0;
	philo->threads[i].last_meal = 0;
	philo->threads[i].left_fork = &philo->forks[i];
	if (i + 1 == philo->number_of_philosophers)
		philo->threads[i].right_fork = &philo->forks[0];
	else
		philo->threads[i].right_fork = &philo->forks[i + 1];
	philo->threads[i].philo_struct = philo;
}

static void	init_philo(t_philo *philo)
{
	pthread_t	*th;
	int			i;

	th = malloc(sizeof(pthread_t) * (philo->number_of_philosophers + 1));
	philo->threads = malloc(sizeof(t_thread) * philo->number_of_philosophers);
	philo->start_time = get_time();
	init_mutex(philo);
	i = 0;
	while (i < (philo->number_of_philosophers + 1))
	{
		if (i == philo->number_of_philosophers)
			pthread_create(&th[i], NULL, &check_death, philo);
		else
		{
			init_threads(philo, i);
			create_threads(philo, th, i);
		}
		i++;
	}
	join_threads(philo, th);
	if (philo->death == 1
		&& !(philo->number_of_philo_fat >= philo->number_of_philosophers))
		printf("\033[91m%lld %d died\n\033[0m", philo->death_time, \
			philo->death_philo);
	destroy_mutex(philo);
	free(th);
	free(philo->threads);
}

void	ft_philo(t_philo *philo)
{
	philo->number_of_philo_fat = 0;
	philo->death = 0;
	init_philo(philo);
}
