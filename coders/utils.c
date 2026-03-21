/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martin <martin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 11:41:11 by martin            #+#    #+#             */
/*   Updated: 2026/03/21 16:13:13 by martin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
	{
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static	int	sign(const char *str, int i, int *neg)
{
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			*neg = -1;
		i++;
	}
	return (i);
}

int	ft_atoi(char *str)
{
	int			i;
	int			neg;
	long long	s;

	i = 0;
	neg = 1;
	s = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	i = sign(str, i, &neg);
	while (str[i] >= '0' && str[i] <= '9')
	{
		s = (s * 10) + (str[i] - '0');
		i++;
	}
	return (s * neg);
}

long long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000LL));
}
