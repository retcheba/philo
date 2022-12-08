/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 12:36:52 by retcheba          #+#    #+#             */
/*   Updated: 2022/12/04 12:36:54 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_thread	t_thread;
typedef struct s_philo	t_philo;

struct s_thread
{
	int				philo;
	long long		last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_philo			*philo_struct;
};

struct s_philo
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				number_of_philo_fat;
	int				death;
	long long		start_time;
	t_thread		*threads;
	pthread_mutex_t	*forks;
	pthread_mutex_t	printf;
	pthread_mutex_t	philo_fat;
	pthread_mutex_t	philo_death;
};

int			ft_atoi(const char *num);
void		ft_philo(t_philo *philo);
void		init_mutex(t_philo *philo);
void		destroy_mutex(t_philo *philo);
void		print_status(t_thread *thread, char	*status, int color);
int			is_a_dead_philo(t_thread *thread);
int			is_only_one_philo(t_thread *thread);
void		print_death(t_thread *thread, long long time);
void		*routine_endless(void *arg);
void		*routine_defined_end(void *arg);
long long	get_time(void);

#endif