/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martin <martin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 19:59:06 by martin            #+#    #+#             */
/*   Updated: 2026/03/22 09:46:37 by martin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	all_done(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->nb_coders)
	{
		if (env->coders[i].nb_compiles < env->compile_req)
			return (0);
		i++;
	}
	return (1);
}

static int	check_burnout(t_env *env, int i)
{
	long long	last_compile_start;

	pthread_mutex_lock(&env->stop_mutex);
	last_compile_start = env->coders[i].last_compile_start;
	pthread_mutex_unlock(&env->stop_mutex);
	if (get_time() - last_compile_start <= env->time_bo)
		return (0);
	pthread_mutex_lock(&env->stop_mutex);
	env->stop_sim = 1;
	pthread_mutex_unlock(&env->stop_mutex);
	pthread_mutex_lock(&env->log_mutex);
	printf("%lld %d burned out\n",
		get_time() - env->start_time, env->coders[i].id);
	pthread_mutex_unlock(&env->log_mutex);
	return (1);
}

void	*monitor_routine(void *arg)
{
	t_env	*env;
	int		i;

	env = (t_env *)arg;
	while (1)
	{
		pthread_mutex_lock(&env->stop_mutex);
		if (env->stop_sim)
			return (pthread_mutex_unlock(&env->stop_mutex), NULL);
		pthread_mutex_unlock(&env->stop_mutex);
		if (all_done(env))
			return (NULL);
		i = -1;
		while (++i < env->nb_coders)
			if (check_burnout(env, i))
				return (NULL);
		usleep(1000);
	}
}
