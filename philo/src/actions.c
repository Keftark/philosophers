/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpothin <cpothin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 08:50:56 by cpothin           #+#    #+#             */
/*   Updated: 2023/07/17 17:32:14 by cpothin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	action_think(t_data *data, t_philo *philosopher)
{
	pthread_mutex_lock(&data->m_write);
	philosopher->action = THINK;
	printf("%lu %d is thinking\n", get_elapsed_time() - data->start_time,
		philosopher->id);
	pthread_mutex_unlock(&data->m_write);
}

void	action_sleep(t_data *data, t_philo *philosopher)
{
	pthread_mutex_lock(&data->m_write);
	philosopher->action = SLEEP;
	printf("%lu %d is sleeping\n", get_elapsed_time() - data->start_time,
		philosopher->id);
	pthread_mutex_unlock(&data->m_write);
	ft_usleep(data->sleep_delay);
}

// apres l'appel de cette fonction, on arrete le programme
void	action_die(t_data *data, t_philo *philosopher)
{
	pthread_mutex_lock(&data->m_write);
	philosopher->action = DEAD;
	data->philo_died = 1;
	printf("%lu %d died\n", get_elapsed_time() - data->start_time,
		philosopher->id);
	pthread_mutex_unlock(&data->m_write);
}

int	check_meals(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_amount)
	{
		if (data->philos[i]->meals < data->max_eat)
			return (0);
		i++;
	}
	data->finish_eat = 1;
	return (1);
}

int	check_end(t_data *data)
{
	if (!data->finish_eat && !data->philo_died)
		return (0);
	return (1);
}
