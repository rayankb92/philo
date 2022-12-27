/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_dead.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 12:12:41 by rferradi          #+#    #+#             */
/*   Updated: 2022/12/27 18:30:07 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_he_dead(t_philo *philo)
{
	int	dead;
	pthread_mutex_lock(&philo->data->isdeadlock);
	dead = philo->data->isdead;
	pthread_mutex_unlock(&philo->data->isdeadlock);
	return (dead);
}