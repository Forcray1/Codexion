/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martin <martin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 07:13:21 by martin            #+#    #+#             */
/*   Updated: 2026/04/04 07:13:22 by martin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "codexion.h"

static int	check_burnout(t_env *env, int i)
{
	long long	now;

	now = get_time();
	pthread_mutex_lock(&env->stop_mutex);
	if (now - env->coders[i].last_compile_start > env->time_bo)
	{
		env->stop_sim = 1;
		pthread_mutex_unlock(&env->stop_mutex);
		pthread_mutex_lock(&env->log_mutex);
		printf("%lld ms | Coder %d has burned out!\n",
			now - env->start_time, env->coders[i].id);
		pthread_mutex_unlock(&env->log_mutex);
		return (1);
	}
	pthread_mutex_unlock(&env->stop_mutex);
	return (0);
}

static void	all_done(t_env *env, int *done_count)
{
	int	i;

	i = -1;
	*done_count = 0;
	while (++i < env->nb_coders)
	{
		pthread_mutex_lock(&env->stop_mutex);
		if (env->coders[i].nb_compiles >= env->compile_req)
			(*done_count)++;
		pthread_mutex_unlock(&env->stop_mutex);
	}
	if (*done_count == env->nb_coders)
	{
		i = -1;
		while (++i < env->nb_coders)
		{
			pthread_mutex_lock(&env->log_mutex);
			pthread_mutex_unlock(&env->log_mutex);
		}
		pthread_mutex_lock(&env->stop_mutex);
		env->stop_sim = 1;
		pthread_mutex_unlock(&env->stop_mutex);
	}
}

void	*monitor_routine(void *arg)
{
	t_env	*env;
	int		i;
	int		done_count;

	env = (t_env *)arg;
	while (1)
	{
		i = -1;
		while (++i < env->nb_coders)
		{
			if (check_burnout(env, i))
				return (NULL);
		}
		all_done(env, &done_count);
		pthread_mutex_lock(&env->stop_mutex);
		if (env->stop_sim)
		{
			pthread_mutex_unlock(&env->stop_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&env->stop_mutex);
		usleep(1000);
	}
}
