/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 02:06:03 by rferradi          #+#    #+#             */
/*   Updated: 2022/12/27 19:06:50 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define RESET "\033[0m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define BLUE "\033[0;34m"
# define YELLOW "\033[0;93m"
# define MAGENTA "\033[0;95m"
# define BRED "\033[0;41m"
# define BGREEN "\033[0;42m"
# define BBLUE "\033[0;44m"
# define BYELLOW "\033[0;103m"
# define BMAGENTA "\033[0;105m"

typedef struct t_data	t_data;
typedef struct s_philo
{
	long				date;
	int					eat;
	long				lastmeal;
	int					die;
	int					isdead;
	int					sleep;
	int					slept;
	int					each_eat;
	int					eaten;
	int					nbmeal;
	int					index;
	pthread_t			thread;
	pthread_mutex_t		forkleft;
	pthread_mutex_t		*forkright;
	pthread_mutex_t		meallock;
	t_data				*data;
}						t_philo;

typedef struct t_data
{
	t_philo				*phils;
	pthread_mutex_t		print;
	pthread_mutex_t		isdeadlock;
	pthread_mutex_t		nbmeallock;
	int					eat;
	int					die;
	int					sleep;
	int					nbphilo;
	int					nbmeal;
	int					isdead;
	long int			timestart;
	int					argc;
	int					all_eaten;
	pthread_t			death;
}						t_data;

int						ft_atoi(char *str);
void					penser(t_philo *philo);
int						dormir(t_philo *philo);
int						manger(t_philo *philo, t_data *data);
long int				gettime(void);

void					*routine(void *philo);
int						set_data(t_data *data, int argc, char **argv);
int						init_thread(t_data *data);
int						set_philo(t_data *data);
long int				gettime(void);
int						usleep_(long int duration);
int						left_meals(t_philo *phil, int boole);

int						ft_isdead(t_philo *phil);

int						print_mutex(t_philo *philo, char *str, char *color);
int						print_die(t_philo *philo, char *color);
void					*checkdeath(void *data);
int						unlock(pthread_mutex_t **mutex, int size);
long int				gettimstamp(t_data *data);
int						print_status(t_philo *philo, const char *msg);
int						is_he_dead(t_philo *philo);
void					watcher(t_data *data);

#endif

// 0 1 has taken a fork
// 0 1 has taken a fork
// 0 1 is eating
// 0 2 has taken a fork
// 0 2 has taken a fork
// 0 2 is eating
// 200 1 is sleeping
// 200 2 is sleeping
// 200 3 has taken a fork
// 200 3 has taken a fork
// 200 3 is eating
// 200 4 has taken a fork
// 200 4 has taken a fork
// 200 4 is eating
// 400 1 is thinking
// 400 2 is thinking
// 400 3 is sleeping
// 400 5 has taken a fork
// 400 5 has taken a fork
// 400 5 is eating
// 400 4 is sleeping
// 400 1 has taken a fork
// 400 1 has taken a fork
// 400 1 is eating
// 410 2 is dead
