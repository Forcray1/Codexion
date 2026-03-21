/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ressources.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martin <martin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 17:09:53 by martin            #+#    #+#             */
/*   Updated: 2026/03/21 17:42:58 by martin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	init_dongles(t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->nb_coders)
	{
		env->dongles[i].id = i;
		env->dongles[i].is_used = 0;
		env->dongles[i].last_use = 0;

		env->dongles[i].wait_queue.requests = malloc(sizeof(t_request)
				* env->nb_coders);
		if (!env->dongles[i].wait_queue.requests)
			return (1);
		env->dongles[i].wait_queue.size = 0;

		pthread_mutex_init(&env->dongles[i].mutex, NULL);
		pthread_cond_init(&env->dongles[i].cond, NULL);
	}
	return (0);
}

static void	init_coders(t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->nb_coders)
	{
		env->coders[i].id = i + 1;
		env->coders[i].nb_compiles = 0;
		env->coders[i].last_compile_start = env->start_time;
		env->coders[i].env = env;
		env->coders[i].left_dongle = &env->dongles[i];
		env->coders[i].right_dongle = &env->dongles[(i + 1) % env->nb_coders];
	}
}

int	init_resources(t_env *env)
{
	env->coders = malloc(sizeof(t_coder) * env->nb_coders);
	if (!env->coders)
		return (1);
	env->dongles = malloc(sizeof(t_dongle) * env->nb_coders);
	if (!env->dongles)
		return (free(env->coders), 1);
	if (init_dongles(env) != 0)
		return (1);
	init_coders(env);
	return (0);
}