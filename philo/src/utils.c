/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpothin <cpothin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:45:04 by cpothin           #+#    #+#             */
/*   Updated: 2023/07/19 14:18:04 by cpothin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

size_t	ft_atoi(const char *str)
{
	size_t	result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] && (str[i] == '\f' || str[i] == '\t' || str[i] == ' '
			|| str[i] == '\n' || str[i] == '\r' || str[i] == '\v'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i++] - '0';
	}
	result *= sign;
	return (result);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

void	print_message(t_data *data, char *str, int philo)
{
	pthread_mutex_lock(&data->m_state);
	if (data->sim_state != RUNNING && ft_strcmp(str, P_DIED) != 0)
	{
		pthread_mutex_unlock(&data->m_state);
		return ;
	}
	pthread_mutex_unlock(&data->m_state);
	pthread_mutex_lock(&data->m_write);
	printf("%lu %d %s\n", get_elapsed_time() - data->start_time,
		philo, str);
	pthread_mutex_unlock(&data->m_write);
}
