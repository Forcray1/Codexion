/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.C                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martin <martin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 19:56:57 by martin            #+#    #+#             */
/*   Updated: 2026/03/21 20:10:10 by martin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	print_status(t_coder *coder, char *status)
{
	long long	now;

	pthread_mutex_lock(&coder->env->stop_mutex);
	if (coder->env->stop_sim)
	{
		pthread_mutex_unlock(&coder->env->stop_mutex);
		return ;
	}
	pthread_mutex_unlock(&coder->env->stop_mutex);
	pthread_mutex_lock(&coder->env->log_mutex);
	now = get_time() - coder->env->start_time;
	printf("%lld ms | Coder %d %s\n", now, coder->id, status);
	pthread_mutex_unlock(&coder->env->log_mutex);
}

int	check_stop(t_env *env)
{
	int	res;

	pthread_mutex_lock(&env->stop_mutex);
	res = env->stop_sim;
	pthread_mutex_unlock(&env->stop_mutex);
	return (res);
}

void	wait_for_start(t_env *env)
{
	while (get_time() < env->start_time)
		usleep(100);
}

int	must_stop(t_env *env)
{
	int	stop;

	pthread_mutex_lock(&env->stop_mutex);
	stop = env->stop_sim;
	pthread_mutex_unlock(&env->stop_mutex);
	return (stop);
}