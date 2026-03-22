/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martin <martin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 16:19:18 by martin            #+#    #+#             */
/*   Updated: 2026/03/22 09:53:04 by martin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	take_dongles(t_coder *coder)
{
	t_env	*env;
	int		first;
	int		second;

	env = coder->env;
	first = coder->id;
	second = (coder->id + 1) % env->nb_coders;
	if (first > second)
	{
		first = second;
		second = coder->id;
	}
	pthread_mutex_lock(&env->dongles[first].mutex);
	print_status(coder, "has taken a dongle");
	pthread_mutex_lock(&env->dongles[second].mutex);
	print_status(coder, "has taken a dongle");
	return (0);
}

void	drop_dongles(t_coder *coder)
{
	t_env	*env;
	int		left;
	int		right;

	env = coder->env;
	left = coder->id;
	right = (coder->id + 1) % env->nb_coders;
	pthread_mutex_unlock(&env->dongles[left].mutex);
	pthread_mutex_unlock(&env->dongles[right].mutex);
}

static int	do_compile(t_coder *coder)
{
	t_env	*env;

	env = coder->env;
	if (take_dongles(coder) != 0)
		return (1);
	pthread_mutex_lock(&env->stop_mutex);
	coder->last_compile_start = get_time();
	pthread_mutex_unlock(&env->stop_mutex);
	print_status(coder, "is compiling");
	action_sleep(env->time_compile, env);
	coder->nb_compiles++;
	drop_dongles(coder);
	return (0);
}

void	*coder_routine(void *arg)
{
	t_coder	*coder;
	t_env	*env;

	coder = (t_coder *)arg;
	env = coder->env;
	wait_for_start(env);
	while (!must_stop(env) && coder->nb_compiles < env->compile_req)
	{
		if (do_compile(coder))
			break ;
		if (must_stop(env))
			break ;
		print_status(coder, "is debugging");
		action_sleep(env->time_debug, env);
		if (must_stop(env))
			break ;
		print_status(coder, "is refactoring");
		action_sleep(env->time_refract, env);
	}
	return (NULL);
}

int	launch_simulation(t_env *env)
{
	int			i;
	pthread_t	monitor_thread;

	env->start_time = get_time();
	i = 0;
	while (i < env->nb_coders)
	{
		env->coders[i].last_compile_start = env->start_time;
		if (pthread_create(&env->coders[i].thread, NULL,
				&coder_routine, &env->coders[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, &monitor_routine, env) != 0)
		return (1);
	i = 0;
	while (i < env->nb_coders)
	{
		pthread_join(env->coders[i].thread, NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
	return (0);
}
