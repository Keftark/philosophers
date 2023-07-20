/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpothin <cpothin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:11:13 by cpothin           #+#    #+#             */
/*   Updated: 2023/07/19 15:36:30 by cpothin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>

# define P_DIED "died"

typedef enum Action
{
	THINK,
	TRYING_TO_EAT,
	EAT,
	SLEEP,
	DEAD
}				t_action;

typedef enum SimState
{
	RUNNING,
	DEATH,
	FINISH
}				t_sim_state;

typedef struct s_data	t_data;

typedef struct s_philo
{
	t_data			*data;
	pthread_t		tid;
	pthread_t		death_id;
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
	pthread_mutex_t		m_state;
	pthread_mutex_t		m_time;
	pthread_mutex_t		m_meals;
	t_philo				**philos;
	int					cur_philo;
	suseconds_t			start_time;
	suseconds_t			eat_delay;
	suseconds_t			sleep_delay;
	suseconds_t			die_delay;
	int					philos_amount;
	int					eat_n_times;
	t_sim_state			sim_state;
	int					max_eat;
};

void				action_think(t_data *data, t_philo *philo);
void				action_sleep(t_data *data, t_philo *philo);
void				action_die(t_data *data, t_philo *philo);
void				init_threads(t_data *data);
void				init_philos(t_data *data);
void				free_all(t_data *data);
void				*life_cycle(void *phil);
void				ft_usleep(suseconds_t time_in_ms);
void				stop_threads(t_data *data);
void				print_message(t_data *data, char *str, int philo);
void				set_start_eat_timer(t_data *data, t_philo *philo);
size_t				ft_atoi(const char *str);
int					check_args(int argc, char *argv[]);
int					check_meals(t_data *data);
int					check_end(t_data *data);
suseconds_t			get_elapsed_time(void);

#endif