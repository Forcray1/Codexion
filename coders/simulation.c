/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martin <martin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 16:19:18 by martin            #+#    #+#             */
/*   Updated: 2026/03/21 21:59:13 by martin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	print_env(t_env *e)
{
	printf("--- ENV DEBUG ---\n");
	printf("Coders: %d | BO: %d | Comp: %d | Debug: %d\n",
		e->nb_coders, e->time_bo, e->time_compile, e->time_debug);
	printf("Refactor: %d | Req: %d | CD: %d | Sched: %d\n",
		e->time_refract, e->compile_req, e->dongle_cd, e->scheduler);
	printf("-----------------\n");
}


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

void	*coder_routine(void *arg)
{
	t_coder	*coder;
	t_env	*env;

	coder = (t_coder *)arg;
	env = coder->env;
	wait_for_start(env);
	while (1)
	{
		if (must_stop(env) || coder->nb_compiles >= env->compile_req)
			break ;
		print_status(coder, "is refactoring");
		action_sleep(env->time_refract, env);
		if (take_dongles(coder) != 0)
			break ;
		print_status(coder, "is compiling");
		action_sleep(env->time_compile, env);
		coder->nb_compiles++;
		drop_dongles(coder);
		print_status(coder, "is debugging");
		action_sleep(env->time_debug, env);
	}
	return (NULL);
}

int	launch_simulation(t_env *env)
{
	int	i;

	env->start_time = get_time();
	i = 0;
	while (i < env->nb_coders)
	{
		if (pthread_create(&env->coders[i].thread, NULL,
				&coder_routine, &env->coders[i]) != 0)
		{
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < env->nb_coders)
	{
		pthread_join(env->coders[i].thread, NULL);
		i++;
	}
	return (0);
}
