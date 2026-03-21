/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martin <martin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 19:59:06 by martin            #+#    #+#             */
/*   Updated: 2026/03/21 21:59:43 by martin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	*monitor_routine(void *arg)
{
	t_env	*env;
	int		i;

	env = (t_env *)arg;
	while (1)
	{
		i = -1;
		while (++i < env->nb_coders)
		{
			pthread_mutex_lock(&env->stop_mutex);
			if (get_time() - env->coders[i].last_compile_start
				> env->time_bo)
			{
				env->stop_sim = 1;
				pthread_mutex_unlock(&env->stop_mutex);
				pthread_mutex_lock(&env->log_mutex);
				printf("%lld ms | Coder %d has burned out!\n",
					get_time() - env->start_time, env->coders[i].id);
				pthread_mutex_unlock(&env->log_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&env->stop_mutex);
		}
		usleep(1000);
	}
}
