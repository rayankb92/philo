/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 01:56:41 by rferradi          #+#    #+#             */
/*   Updated: 2022/12/27 19:12:59 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_data(t_data *data, int argc, char **argv)
{
	data->phils = malloc(sizeof(t_philo) * (ft_atoi(argv[1])));
	if (!data->phils)
		return (0);
	pthread_mutex_init(&data->nbmeallock, NULL);
	pthread_mutex_init(&data->isdeadlock, NULL);
	pthread_mutex_init(&data->print, NULL);
	data->nbphilo = ft_atoi(argv[1]);
	data->die = ft_atoi(argv[2]);
	data->eat = ft_atoi(argv[3]);
	data->sleep = ft_atoi(argv[4]);
	data->argc = argc;
	data->isdead = 0;
	if (argc == 6)
		data->nbmeal = ft_atoi(argv[5]);
	return (1);
}

int	init_thread(t_data *data)
{
	int i ;
	
	i = -1;
	data->timestart = gettime();
	while (++i < data->nbphilo)
		pthread_create(&data->phils[i].thread, NULL, &routine, &data->phils[i]);
	watcher(data);
	i = -1;
	while (++i < data->nbphilo)
			pthread_join(data->phils[i].thread, NULL);
	return (1);
}

int	set_philo(t_data *data)
{
	int	i;

	i = -1;
	memset(data->phils, 0, sizeof(t_philo) * data->nbphilo); 
	while (++i < data->nbphilo)
	{
		pthread_mutex_init(&data->phils[i].meallock, NULL);
		data->phils[i].eat = data->eat;
		data->phils[i].die = data->die;
		data->phils[i].sleep = data->sleep;
		data->phils[i].index = i + 1;
		data->phils[i].data = data;
		data->phils[i].lastmeal = gettime();
		data->phils[i].each_eat = 0;
		data->phils[i].nbmeal = data->nbmeal;
		if (pthread_mutex_init( &data->phils[i].forkleft, NULL))
			return (0);
		if (i == data->nbphilo - 1)
			data->phils[i].forkright = &data->phils[0].forkleft;
		else
			data->phils[i].forkright = &data->phils[i + 1].forkleft;
	}
	return (1);
}