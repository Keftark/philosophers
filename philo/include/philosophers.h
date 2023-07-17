/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpothin <cpothin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:11:13 by cpothin           #+#    #+#             */
/*   Updated: 2023/07/17 17:36:15 by cpothin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>

typedef enum Action
{
	THINK,
	TRYING_TO_EAT,
	EAT,
	SLEEP,
	DEAD
}				t_action;

typedef struct s_data t_data;

typedef struct s_philo
{
	t_data			*data;
	pthread_t		tid;
	pthread_t		death_id;
	t_action		action;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	suseconds_t		start_eat_time;
	suseconds_t		die_delay;
	int				meals;
	int				id;
}				t_philo;

struct s_data
{
	pthread_mutex_t		*forks;
	pthread_mutex_t		m_write;
	pthread_mutex_t		m_data;
	t_philo				**philos;
	int					cur_philo;
	suseconds_t			start_time;
	suseconds_t			eat_delay;
	suseconds_t			sleep_delay;
	suseconds_t			die_delay;
	int					philos_amount;
	int					eat_n_times;
	int					philo_died;
	int					max_eat;
	int					finish_eat;
};

void				action_think(t_data *data, t_philo *philosopher);
void				action_sleep(t_data *data, t_philo *philosopher);
void				action_die(t_data *data, t_philo *philosopher);
void    			init_threads(t_data *data);
void				init_philos(t_data *data);
void				free_all(t_data *data);
void				*life_cycle(void *phil);
void				ft_usleep(suseconds_t time_in_ms);
void				stop_threads(t_data *data);
size_t				ft_atoi(const char *str);
int					check_args(int argc, char *argv[]);
int					check_meals(t_data *data);
int					check_end(t_data *data);
suseconds_t			get_elapsed_time();

#endif