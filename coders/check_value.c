/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martin <martin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 10:47:47 by martin            #+#    #+#             */
/*   Updated: 2026/03/22 09:55:53 by martin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	check_value2(char **argv)
{
	if (ft_atoi(argv[5]) <= 0)
	{
		printf("time to refractor should be a positive integer not null");
		return (1);
	}
	if (ft_atoi(argv[6]) <= 0)
	{
		printf("number of compile requiered should be a positive ");
		printf("integer not null");
		return (1);
	}
	if (ft_atoi(argv[7]) < 0)
	{
		printf("Dongle cooldown should be a positive integer");
		return (1);
	}
	if ((ft_strcmp(argv[8], "fifo") != 0) && (ft_strcmp(argv[8], "edf") != 0))
	{
		printf("scheduler have to be either 'fifo' or 'edf'");
		return (1);
	}
	return (0);
}

int	check_value(char **argv)
{
	if (ft_atoi(argv[1]) <= 0)
	{
		printf("number of coder should be a positive integer not null");
		return (1);
	}
	if (ft_atoi(argv[2]) <= 0)
	{
		printf("time to burnout should be a positive integer not null");
		return (1);
	}
	if (ft_atoi(argv[3]) <= 0)
	{
		printf("time to compile should be a positive integer not null");
		return (1);
	}
	if (ft_atoi(argv[4]) <= 0)
	{
		printf("time to debug should be a positive integer not null");
		return (1);
	}
	if (check_value2(argv) == 1)
		return (1);
	return (0);
}
