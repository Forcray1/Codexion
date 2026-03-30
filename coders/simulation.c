/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martin <martin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 16:19:18 by martin            #+#    #+#             */
/*   Updated: 2026/03/30 20:18:47 by martin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	do_compile(t_coder *coder)
{
	if (take_dongles(coder) != 0)
		return (1);
	print_status(coder, "is compiling");
	action_sleep((long long)coder->env->time_compile, coder->env);
	coder->nb_compiles++;
	drop_dongles(coder);
	return (0);
}

static int	should_stop(t_coder *c, t_env *e)
{
	if (must_stop(e) != 0)
		return (1);
	if (e->compile_req != -1)
	{
		if (c->nb_compiles >= e->compile_req)
			return (1);
	}
	return (0);
}

void	*coder_routine(void *arg)
{
	t_coder	*c;
	t_env	*e;

	c = (t_coder *)arg;
	e = c->env;
	wait_for_start(e);
	while (should_stop(c, e) == 0)
	{
		if (do_compile(c) != 0 || should_stop(c, e) != 0)
			break ;
		print_status(c, "is debugging");
		action_sleep((long long)e->time_debug, e);
		if (must_stop(e) != 0)
			break ;
		print_status(c, "is refactoring");
		action_sleep((long long)e->time_refract, e);
	}
	if (must_stop(e) == 0 && e->compile_req != -1)
	{
		if (c->nb_compiles >= e->compile_req)
			print_status(c, "is done");
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
