/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martin <martin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 16:19:18 by martin            #+#    #+#             */
/*   Updated: 2026/03/21 19:12:02 by martin           ###   ########.fr       */
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

void	*coder_routine(void *arg)
{
	t_coder	*coder;
	t_env	*env;

	coder = (t_coder *)arg;
	env = coder->env;
	while (1)
	{
		/*
		1. Verifier si on doit s'arreter (Burnout ou Finish)
		2. Refactor (penser)
		3. Prendre les dongles
		4. Compiler
		5. Relacher les dongles
		Pour l'instant on met un break pour ne pas faire de boucle infinie
		*/
		break ;
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
