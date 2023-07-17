/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpothin <cpothin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:03:37 by cpothin           #+#    #+#             */
/*   Updated: 2023/07/17 17:31:21 by cpothin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void    cycle_think(t_data *data, t_philo *philo)
{
	if (check_end(data))
		return ;
    action_think(data, philo);
}

void    cycle_sleep(t_data *data, t_philo *philo)
{
	if (check_end(data))
		return ;
    action_sleep(data, philo);
	ft_usleep(data->sleep_delay);
}

void	*death_thread(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	ft_usleep(philo->die_delay + 2);
	// si aucun philo n'est deja mort, on meurt...
	if (philo->action == TRYING_TO_EAT && !check_end(philo->data))
		action_die(philo->data, philo);
	return (NULL);
}

void    cycle_eat(t_data *data, t_philo *philo)
{
	philo->action = TRYING_TO_EAT;
	pthread_mutex_lock(philo->left_fork);
    	pthread_mutex_lock(&data->m_write);
	printf("%lu %d has taken a fork\n", get_elapsed_time() - data->start_time,
		philo->id);
	pthread_mutex_unlock(&data->m_write);
	pthread_mutex_lock(philo->right_fork);
    	pthread_mutex_lock(&data->m_write);
	printf("%lu %d has taken a fork\n", get_elapsed_time() - data->start_time,
		philo->id);
	pthread_mutex_unlock(&data->m_write);
	pthread_mutex_lock(&data->m_write);
	philo->action = EAT;
	printf("%lu %d is eating\n", get_elapsed_time() - data->start_time,
		philo->id);
	philo->meals += 1;
	pthread_mutex_unlock(&data->m_write);
	ft_usleep(data->eat_delay);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	*life_cycle(void *dat)
{
	t_data	*data;
	t_philo *philo;

	data = (t_data *)dat;
	// pthread_mutex_lock(&data->m_data);
	philo = data->philos[data->cur_philo++];
	// pthread_mutex_unlock(&data->m_data);
	while (!data->philo_died && data->eat_n_times < data->max_eat && !data->finish_eat)
	{
		philo->start_eat_time = get_elapsed_time();
		pthread_create(&philo->death_id, NULL, &death_thread, philo);
		pthread_detach(philo->death_id);
        cycle_eat(data, philo);
        cycle_sleep(data, philo);
        cycle_think(data, philo);
		if (!check_end(data) && check_meals(data) == 1)
		{
			printf("\nEvery philosopher has eaten enough!\n");
		}
	}
	// trouver un moyen de savoir si les philos
	// ont deja mange ou s'il y en a un qui est mort
	return (NULL);
}
