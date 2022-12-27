/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 05:42:59 by rferradi          #+#    #+#             */
/*   Updated: 2022/12/27 18:50:30 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	gettime(void)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return ((current.tv_sec * 1000) + (current.tv_usec / 1000));
}

long int	gettimstamp(t_data *data)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return (((current.tv_sec * 1000) + (current.tv_usec / 1000) ) - (data->timestart));
}

int	usleep_(long int duration)
{
	long	begin;

	begin = gettime();
	while (gettime() - begin < duration)
		usleep(10);
	return (1);
}
