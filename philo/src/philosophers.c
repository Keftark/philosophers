/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpothin <cpothin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 14:44:02 by cpothin           #+#    #+#             */
/*   Updated: 2023/07/17 17:38:03 by cpothin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	free_all(t_data *data)
{
	int	i;

	printf("\nfreeing...\n");
	i = 0;
	if (data->philos)
	{
		while (i < data->philos_amount)
		{
			// data->philos[i]->left_fork = NULL;
			// data->philos[i]->right_fork = NULL;
			free(data->philos[i++]);
		}
		free(data->philos);
	}
	i = 0;
	if (data->forks)
	{
		while (i < data->philos_amount)
			pthread_mutex_destroy(&data->forks[i++]);
		free(data->forks);
	}
	pthread_mutex_destroy(&data->m_write);
	pthread_mutex_destroy(&data->m_data);
}

void	stop_threads(t_data *data)
{
	(void)data;
}

void	init_data(t_data *data, char *argv[])
{
	data->philos = (t_philo **)malloc(sizeof(t_philo *) * ft_atoi(argv[1]));
	if (!data->philos)
		return ; // faire une fonction quit()
	data->forks = NULL;
	data->philos_amount = ft_atoi(argv[1]);
	data->start_time = get_elapsed_time();
	data->die_delay = ft_atoi(argv[2]);
	data->eat_delay = ft_atoi(argv[3]);
	data->sleep_delay = ft_atoi(argv[4]);
	data->eat_n_times = 0;
	data->philo_died = 0;
	data->cur_philo = 0;
	data->finish_eat = 0;
	if (argv[5])
		data->max_eat = ft_atoi(argv[5]);
	else
		data->max_eat = 9999999;
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (check_args(argc, argv) == 0)
		return (0);
	init_data(&data, argv);
	init_threads(&data);
	init_philos(&data);
/*	- faire le timer de la nourriture et faire mourrir un philo quand c'est trop tard
	- mettre un mutex sur les messages quand on a termine ? (mort ou tout mange)
		pour empecher 
			Every philosopher has eaten enough!
			1601 1 is thinking
*/
	while (!data.philo_died && !data.finish_eat)
		ft_usleep(1);
	free_all(&data);
}
