/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorenzo <mlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 10:50:08 by mlorenzo          #+#    #+#             */
/*   Updated: 2026/04/17 12:39:37 by mlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	can_take_s(t_coder *c, t_dongle *f, t_dongle *s)
{
	if (f == s)
		return (1);
	return (s->wait_queue.size > 0
		&& s->wait_queue.requests[0].coder_id == c->id
		&& get_time() - s->last_use >= c->env->dongle_cd
		&& s->is_used == 0);
}

void	solo_coder_routine(t_coder *c)
{
	print_status(c, "has taken a dongle");
	while (check_stop(c->env) == 0)
		usleep(500);
}

void	check_done(t_coder *c, t_env *e)
{
	int	nb_compiles;

	pthread_mutex_lock(&e->stop_mutex);
	nb_compiles = c->nb_compiles;
	pthread_mutex_unlock(&e->stop_mutex);
	if (must_stop(e) == 0 && nb_compiles >= e->compile_req)
		print_status(c, "is done");
}
