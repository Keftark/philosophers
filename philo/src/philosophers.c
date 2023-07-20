/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpothin <cpothin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 14:44:02 by cpothin           #+#    #+#             */
/*   Updated: 2023/07/20 08:39:24 by cpothin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

// pthread_mutex_destroy(&data->m_time);
// pthread_mutex_destroy(&data->m_state);
void	destroy_mutexs(t_data *data)
{
	pthread_mutex_destroy(&data->m_write);
	pthread_mutex_destroy(&data->m_data);
	pthread_mutex_destroy(&data->m_meals);
}

void	free_all(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philos_amount)
		pthread_join(data->philos[i]->tid, NULL);
	if (data->philos)
	{
		i = 0;
		while (i < data->philos_amount)
			free(data->philos[i++]);
		free(data->philos);
	}
	i = 0;
	if (data->forks)
	{
		while (i < data->philos_amount)
			pthread_mutex_destroy(&data->forks[i++]);
		free(data->forks);
	}
	pthread_mutex_lock(&data->m_write);
	if (data->sim_state == FINISH)
		printf("\nEvery philosopher has eaten enough!\n");
	pthread_mutex_unlock(&data->m_write);
	destroy_mutexs(data);
}

void	stop_threads(t_data *data)
{
	(void)data;
}

void	init_data(t_data *data, char *argv[])
{
	data->philos = (t_philo **)malloc(sizeof(t_philo *) * ft_atoi(argv[1]));
	if (!data->philos)
		return ;
	data->forks = NULL;
	data->philos_amount = ft_atoi(argv[1]);
	data->die_delay = ft_atoi(argv[2]);
	data->eat_delay = ft_atoi(argv[3]);
	data->sleep_delay = ft_atoi(argv[4]);
	data->eat_n_times = 0;
	data->sim_state = RUNNING;
	data->cur_philo = 0;
	if (argv[5])
		data->max_eat = ft_atoi(argv[5]);
	else
		data->max_eat = -1;
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (check_args(argc, argv) == 0)
		return (0);
	init_data(&data, argv);
	init_threads(&data);
	data.start_time = get_elapsed_time();
	init_philos(&data);
	while (1)
	{
		pthread_mutex_lock(&data.m_state);
		if (!data.sim_state == RUNNING)
		{
			pthread_mutex_unlock(&data.m_state);
			free_all(&data);
			return (0);
		}
		pthread_mutex_unlock(&data.m_state);
		ft_usleep(1);
	}
}
