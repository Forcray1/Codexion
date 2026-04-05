/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martin <martin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 16:59:28 by martin            #+#    #+#             */
/*   Updated: 2026/03/30 20:21:42 by martin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	cleanup_dongles(t_env *env)
{
	int	i;

	if (!env->dongles)
		return ;
	i = 0;
	while (i < env->nb_coders)
	{
		pthread_mutex_destroy(&env->dongles[i].mutex);
		pthread_cond_destroy(&env->dongles[i].cond);
		if (env->dongles[i].wait_queue.requests)
			free(env->dongles[i].wait_queue.requests);
		i++;
	}
	free(env->dongles);
}

void	final_cleanup(t_env *env)
{
	if (!env)
		return ;
	pthread_mutex_destroy(&env->log_mutex);
	pthread_mutex_destroy(&env->stop_mutex);
	cleanup_dongles(env);
	if (env->coders)
		free(env->coders);
}
