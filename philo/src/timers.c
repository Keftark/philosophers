/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpothin <cpothin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 08:34:26 by cpothin           #+#    #+#             */
/*   Updated: 2023/07/15 09:21:48 by cpothin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

suseconds_t	get_elapsed_time()
{
	struct timeval	start_time;

	gettimeofday(&start_time, NULL);
	return (start_time.tv_sec * 1000 + start_time.tv_usec / 1000);
}

void	ft_usleep(suseconds_t time_in_ms)
{
	suseconds_t	start_time;

	start_time = 0;
	start_time = get_elapsed_time();
	while ((get_elapsed_time() - start_time) < time_in_ms)
		usleep(time_in_ms / 10);
}
