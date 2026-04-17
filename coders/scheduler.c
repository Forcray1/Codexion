/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martin <martin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 20:04:09 by martin            #+#    #+#             */
/*   Updated: 2026/03/31 10:32:47 by martin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	enqueue_request(t_coder *c, t_dongle *d, long long prio)
{
	int			i;
	t_request	tmp;

	pthread_mutex_lock(&d->mutex);
	d->wait_queue.requests[d->wait_queue.size].coder_id = c->id;
	d->wait_queue.requests[d->wait_queue.size].priority_val = prio;
	d->wait_queue.size++;
	i = d->wait_queue.size - 1;
	while (i > 0 && d->wait_queue.requests[i].priority_val
		< d->wait_queue.requests[i - 1].priority_val)
	{
		tmp = d->wait_queue.requests[i];
		d->wait_queue.requests[i] = d->wait_queue.requests[i - 1];
		d->wait_queue.requests[i - 1] = tmp;
		i--;
	}
	pthread_mutex_unlock(&d->mutex);
}

static void	dequeue_request(t_coder *c, t_dongle *d)
{
	int	i;
	int	found;

	pthread_mutex_lock(&d->mutex);
	i = -1;
	found = 0;
	while (++i < d->wait_queue.size)
	{
		if (found)
			d->wait_queue.requests[i - 1] = d->wait_queue.requests[i];
		if (d->wait_queue.requests[i].coder_id == c->id)
			found = 1;
	}
	if (found)
		d->wait_queue.size--;
	pthread_mutex_unlock(&d->mutex);
}

static int	try_take(t_coder *c, t_dongle *f, t_dongle *s)
{
	int	can_take;

	can_take = 0;
	pthread_mutex_lock(&f->mutex);
	if (f != s)
		pthread_mutex_lock(&s->mutex);
	if (f->wait_queue.size > 0
		&& f->wait_queue.requests[0].coder_id == c->id
		&& get_time() - f->last_use >= c->env->dongle_cd
		&& f->is_used == 0
		&& (f == s || (s->wait_queue.size > 0
			&& s->wait_queue.requests[0].coder_id == c->id
			&& get_time() - s->last_use >= c->env->dongle_cd
			&& s->is_used == 0)))
	{
		f->is_used = 1;
		if (f != s)
			s->is_used = 1;
		can_take = 1;
	}
	if (f != s)
		pthread_mutex_unlock(&s->mutex);
	pthread_mutex_unlock(&f->mutex);
	return (can_take);
}

int	take_dongles(t_coder *c)
{
	long long	prio;
	t_dongle	*f;
	t_dongle	*s;

	prio = get_time();
	if (c->env->scheduler == 1)
		prio = c->last_compile_start + c->env->time_bo;
	f = c->left_dongle;
	s = c->right_dongle;
	if (f > s)
	{
		f = c->right_dongle;
		s = c->left_dongle;
	}
	enqueue_request(c, f, prio);
	enqueue_request(c, s, prio);
	while (check_stop(c->env) == 0)
	{
		if (try_take(c, f, s))
			return (print_status(c, "has taken a dongle"),
				print_status(c, "has taken a dongle"),
				dequeue_request(c, f), dequeue_request(c, s), 0);
		usleep(500);
	}
	return (dequeue_request(c, f), dequeue_request(c, s), 1);
}

void	drop_dongles(t_coder *coder)
{
	t_dongle	*f;
	t_dongle	*s;
	long long	now;

	f = coder->left_dongle;
	s = coder->right_dongle;
	if (f > s)
	{
		f = coder->right_dongle;
		s = coder->left_dongle;
	}
	pthread_mutex_lock(&f->mutex);
	if (f != s)
		pthread_mutex_lock(&s->mutex);
	now = get_time();
	f->last_use = now;
	f->is_used = 0;
	if (f != s)
	{
		s->last_use = now;
		s->is_used = 0;
	}
	print_status(coder, "has dropped dongles");
	if (f != s)
		pthread_mutex_unlock(&s->mutex);
	pthread_mutex_unlock(&f->mutex);
}
