/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 18:15:03 by rferradi          #+#    #+#             */
/*   Updated: 2022/12/27 19:14:09 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	watcher(t_data *data)
{
	size_t	i;
	long	time;
	t_philo	*philo;

	philo = data->phils;
	i = -1;
	while (1)
	{
		i = -1;
		while (++i < data->nbphilo)
		{
			pthread_mutex_lock(&philo[i].meallock);
			time = gettime() - philo[i].lastmeal;
			pthread_mutex_unlock(&philo[i].meallock);
			if (time >= data->die)
			{
				pthread_mutex_lock(&data->isdeadlock);
				data->isdead = 1;
				pthread_mutex_unlock(&data->isdeadlock);
				pthread_mutex_lock(&data->print);
				printf("%li %i died\n", gettimstamp(philo->data), philo->index);
				pthread_mutex_unlock(&data->print);
				return ;
			}
			pthread_mutex_lock(&data->nbmeallock);
			if (data->nbmeal == -1)
			{
				pthread_mutex_unlock(&data->nbmeallock);
				return ;
			}
			pthread_mutex_unlock(&data->nbmeallock);
		}
		usleep(100);
	}
}