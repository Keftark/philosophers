/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpothin <cpothin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 08:51:02 by cpothin           #+#    #+#             */
/*   Updated: 2023/07/17 17:36:51 by cpothin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void    init_threads(t_data *data)
{
	int i;

	if (pthread_mutex_init(&data->m_write, NULL) != 0)
		free_all(data);
	if (pthread_mutex_init(&data->m_data, NULL) != 0)
		free_all(data);
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
		* data->philos_amount);
	if (!data->forks)
		return (free_all(data));
	i = 0;
	while (i < data->philos_amount)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			free_all(data);
		i++;
	}
}

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_amount)
	{
		data->philos[i] = (t_philo *)malloc(sizeof(t_philo));
		if (!data->philos[i])
			return (free_all(data));
		//data->philos[i].start_time = get_elapsed_time(data); // on enregistre le timer de base
		// on start un thread
		data->philos[i]->data = data;
		data->philos[i]->die_delay = data->die_delay;
		data->philos[i]->left_fork = &data->forks[i];
		if (i + 1 == data->philos_amount)
			data->philos[i]->right_fork = &data->forks[0];
		else
			data->philos[i]->right_fork = &data->forks[i + 1];
		data->philos[i]->meals = 0;
		data->philos[i]->id = i + 1;
		data->philos[i]->action = THINK;
		pthread_mutex_lock(&data->m_data);
		if (pthread_create(&data->philos[i]->tid, NULL,
			life_cycle, (void *)data) != 0) // routine = la fonction qui va gerer le philo
		{
			// si ca echoue, on quitte en detruisant tous les threads et tout
			return (free_all(data));
			//destroy(args, forks, philos);
			//return (panic(THREAD_CREATE_ERR)); // simple message d'erreur
		}
		pthread_mutex_unlock(&data->m_data);
		i++;
	}
}
