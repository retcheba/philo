/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 23:23:28 by retcheba          #+#    #+#             */
/*   Updated: 2022/10/12 23:28:07 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_wrong_arguments(t_philo *philo)
{
	if (philo->number_of_philosophers == 0)
		return (1);
	else if (philo->time_to_die == 0)
		return (1);
	else if (philo->time_to_eat == 0)
		return (1);
	else if (philo->time_to_sleep == 0)
		return (1);
	else if (philo->number_of_times_each_philosopher_must_eat == 0)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	philo;

	if (argc == 5 || argc == 6)
	{
		philo.number_of_philosophers = ft_atoi(argv[1]);
		philo.time_to_die = ft_atoi(argv[2]);
		philo.time_to_eat = ft_atoi(argv[3]);
		philo.time_to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			philo.number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
		else
			philo.number_of_times_each_philosopher_must_eat = -1;
		if (is_wrong_arguments(&philo))
			printf("Error: Wrong arguments\n");
		else
			ft_philo(&philo);
	}
	else
		printf("Error: Wrong number of arguments\n");
	return (0);
}
