/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpothin <cpothin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 08:51:02 by cpothin           #+#    #+#             */
/*   Updated: 2023/07/19 15:19:47 by cpothin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	init_threads(t_data *data)
{
	int	i;

	if (pthread_mutex_init(&data->m_write, NULL) != 0)
		return ;
	if (pthread_mutex_init(&data->m_data, NULL) != 0)
		return ;
	if (pthread_mutex_init(&data->m_state, NULL) != 0)
		return ;
	if (pthread_mutex_init(&data->m_time, NULL) != 0)
		return ;
	if (pthread_mutex_init(&data->m_meals, NULL) != 0)
		return ;
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->philos_amount);
	if (!data->forks)
		return ;
	i = 0;
	while (i < data->philos_amount)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return ;
		i++;
	}
}

void	give_forks(t_data *data, t_philo *philo, int index)
{
	philo->left_fork = &data->forks[index];
	if (data->philos_amount == 1)
		philo->right_fork = NULL;
	else
	{
		if (index + 1 == data->philos_amount)
			philo->right_fork = &data->forks[0];
		else
			philo->right_fork = &data->forks[index + 1];
	}
}

void	init_philos(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < data->philos_amount)
	{
		data->philos[i] = (t_philo *)malloc(sizeof(t_philo));
		if (!data->philos[i])
			return ;
		philo = data->philos[i];
		philo->data = data;
		philo->die_delay = data->die_delay;
		give_forks(data, philo, i);
		philo->meals = 0;
		philo->id = i + 1;
		pthread_mutex_lock(&data->m_data);
		if (pthread_create(&philo->tid, NULL,
				life_cycle, (void *)data) != 0)
			return ;
		pthread_mutex_unlock(&data->m_data);
		i++;
	}
}
