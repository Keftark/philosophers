/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpothin <cpothin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:46:09 by cpothin           #+#    #+#             */
/*   Updated: 2023/07/11 16:10:42 by cpothin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int ft_isdigit(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] < '0' || str[i] > '9')
			return (0);
	return (1);
}

int	check_args(int argc, char *argv[])
{
	int i;

	i = 0;
	if (argc < 5 || argc > 6)
		return (0);
	while (++i < argc)
		if (!ft_isdigit(argv[i]))
			return (0);
	return (1);
}