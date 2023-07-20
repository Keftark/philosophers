/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpothin <cpothin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 08:50:56 by cpothin           #+#    #+#             */
/*   Updated: 2023/07/20 08:41:55 by cpothin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	action_think(t_data *data, t_philo *philo)
{
	print_message(data, "is thinking", philo->id);
}

void	action_sleep(t_data *data, t_philo *philo)
{
	print_message(data, "is sleeping", philo->id);
	ft_usleep(data->sleep_delay);
}

void	action_die(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->m_state);
	data->sim_state = DEATH;
	pthread_mutex_unlock(&data->m_state);
	print_message(data, "died", philo->id);
}

int	check_meals(t_data *data)
{
	int	i;

	i = 0;
	if (data->max_eat == -1)
		return (0);
	while (i < data->philos_amount)
	{
		pthread_mutex_lock(&data->m_meals);
		if (data->philos[i]->meals < data->max_eat)
		{
			pthread_mutex_unlock(&data->m_meals);
			return (0);
		}
		pthread_mutex_unlock(&data->m_meals);
		i++;
	}
	pthread_mutex_lock(&data->m_state);
	data->sim_state = FINISH;
	pthread_mutex_unlock(&data->m_state);
	return (1);
}

int	check_end(t_data *data)
{
	pthread_mutex_lock(&data->m_state);
	if (data->sim_state == RUNNING)
	{
		pthread_mutex_unlock(&data->m_state);
		return (0);
	}
	pthread_mutex_unlock(&data->m_state);
	return (1);
}
