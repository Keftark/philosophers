/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpothin <cpothin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:03:37 by cpothin           #+#    #+#             */
/*   Updated: 2023/07/19 16:35:20 by cpothin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	cycle_think(t_data *data, t_philo *philo)
{
	if (check_end(data))
		return ;
	action_think(data, philo);
}

void	cycle_sleep(t_data *data, t_philo *philo)
{
	if (check_end(data))
		return ;
	action_sleep(data, philo);
	cycle_think(data, philo);
}

void	*death_thread(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	ft_usleep(philo->die_delay + 1);
	pthread_mutex_lock(&philo->data->m_time);
	if ((get_elapsed_time() - philo->data->start_time
			- philo->start_eat_time) >= philo->data->die_delay
		&& !check_end(philo->data))
	{
		pthread_mutex_unlock(&philo->data->m_time);
		action_die(philo->data, philo);
	}
	else
		pthread_mutex_unlock(&philo->data->m_time);
	return (NULL);
}

void	cycle_eat(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_message(data, "has taken a fork", philo->id);
	if (!philo->right_fork)
		return (ft_usleep(data->eat_delay));
	pthread_mutex_lock(philo->right_fork);
	print_message(data, "has taken a fork", philo->id);
	print_message(data, "is eating", philo->id);
	pthread_mutex_lock(&data->m_meals);
	philo->meals += 1;
	pthread_mutex_unlock(&data->m_meals);
	pthread_mutex_lock(&data->m_time);
	philo->start_eat_time = get_elapsed_time() - data->start_time;
	pthread_mutex_unlock(&data->m_time);
	ft_usleep(data->eat_delay);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	cycle_sleep(data, philo);
}

void	*life_cycle(void *dat)
{
	t_data	*data;
	t_philo	*philo;

	data = (t_data *)dat;
	pthread_mutex_lock(&data->m_data);
	philo = data->philos[data->cur_philo++];
	pthread_mutex_unlock(&data->m_data);
	(philo->id % 2 == 0) && (ft_usleep(data->eat_delay / 10), 1);
	set_start_eat_timer(data, philo);
	while (1)
	{
		pthread_mutex_lock(&data->m_state);
		if (data->sim_state != RUNNING)
		{
			pthread_mutex_unlock(&data->m_state);
			break ;
		}
		pthread_mutex_unlock(&data->m_state);
		pthread_create(&philo->death_id, NULL, &death_thread, philo);
		cycle_eat(data, philo);
		pthread_detach(philo->death_id);
		if (check_meals(data) == 1 && !check_end(data))
			return (NULL);
	}
	return (NULL);
}
