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

#include "philo.h"

void	*routine()
{
	printf("Test from threads\n");
	sleep(2);
	printf("Ending thread\n");
	return (NULL);
}

void	init_threads(t_philo *philo)
{
	(void)philo;
	pthread_t	t1, t2;
	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
		return ;
	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
		return ;
	if (pthread_join(t1, NULL) != 0)
		return ;
	if (pthread_join(t2, NULL) != 0)
		return ;
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
