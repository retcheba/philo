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

void	ft_philo(t_philo *philo)
{
	printf("number_of_philosophers=%ld\n", philo->number_of_philosophers);
	printf("time_to_die=%ld\n", philo->time_to_die);
	printf("time_to_eat=%ld\n", philo->time_to_eat);
	printf("time_to_sleep=%ld\n", philo->time_to_sleep);
	printf("number_of_times_each_philosopher_must_eat=%ld\n", \
		philo->number_of_times_each_philosopher_must_eat);
}
