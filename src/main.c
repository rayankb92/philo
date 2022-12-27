/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 11:37:37 by rferradi          #+#    #+#             */
/*   Updated: 2022/12/27 19:09:07 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	unlock(pthread_mutex_t **mutex, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		pthread_mutex_unlock(mutex[i]);
	return (EXIT_FAILURE);
}

int	print_status(t_philo *philo, const char *msg)
{
	pthread_mutex_lock(&philo->data->print);
	if (is_he_dead(philo))
	{
		pthread_mutex_unlock(&philo->data->print);
		return (1);
	}
	printf("%li %i %s\n", gettimstamp(philo->data), philo->index, msg);
	pthread_mutex_unlock(&philo->data->print);
	return (0);
}

int	take_forkeat(t_philo *philo)
{
	pthread_mutex_t *mutex[2] = {&philo->forkleft, philo->forkright};
	const int pair = philo->index % 2 > 0;
	pthread_mutex_lock(mutex[pair]);
	if (print_status(philo, "Take a fork"))
	{
		pthread_mutex_unlock(mutex[pair]);
		return (EXIT_FAILURE);
	}
	if (mutex[0] == mutex[1])
	{
		pthread_mutex_unlock(mutex[pair]);
		return (1);
	}
	pthread_mutex_lock(mutex[!pair]);
	if (print_status(philo, "Take a fork"))
		return (unlock(mutex, 2));
	if (print_status(philo, "is eating"))
		return (unlock(mutex, 2));
	pthread_mutex_lock(&philo->meallock);
	philo->lastmeal = gettime();
	pthread_mutex_unlock(&philo->meallock);
	usleep_(philo->eat);
	philo->each_eat++;
	pthread_mutex_unlock(mutex[!pair]);
	pthread_mutex_unlock(mutex[pair]);
	if (philo->each_eat == philo->nbmeal)
	{
		pthread_mutex_lock(&philo->data->nbmeallock);
		philo->data->nbmeal--;
		pthread_mutex_unlock(&philo->data->nbmeallock);
		return (1);
	}
	return (EXIT_SUCCESS);
}

int	sleeping(t_philo *philo)
{
	if (print_status(philo, "is sleeeeping"))
		return (EXIT_FAILURE);
	usleep_(philo->sleep);
	return (EXIT_SUCCESS);
}

void	*routine(void *philo)
{
	t_philo *phil;

	phil = (t_philo *)philo;
	if (!(phil->index % 2))
		usleep(phil->eat * 0.8);
	while (1)
	{
		if (phil->data->nbphilo % 2 && phil->each_eat)
			usleep_(phil->die * 0.25);
		if (take_forkeat(phil))
			break;
		if (sleeping(phil))
			break;
		if (print_status(phil, "is thinking"))
			break;
	}
	return (NULL);
}

int	check_arg(t_data *data, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (0);
	if (!set_data(data, argc, argv) || !set_philo(data))
		return (0);
	init_thread(data);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (!check_arg(&data, argc, argv))
		return (0);
	int i = -1;
	
	while (++i < data.nbphilo)
		pthread_mutex_destroy(&data.phils[i].forkleft);
	free(data.phils);
}