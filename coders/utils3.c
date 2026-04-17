/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorenzo <mlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 10:50:08 by mlorenzo          #+#    #+#             */
/*   Updated: 2026/04/17 10:51:04 by mlorenzo         ###   ########.fr       */
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
