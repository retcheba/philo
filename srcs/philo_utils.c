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

#include "philo.h"

size_t	ft_atoi(const char *num)
{
	size_t	result;
	size_t	i;

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
