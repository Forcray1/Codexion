/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martin <martin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 16:19:18 by martin            #+#    #+#             */
/*   Updated: 2026/03/21 17:34:51 by martin           ###   ########.fr       */
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

int	launch_simulation(struct s_env *env)
{
	print_env(env);
	return (0);
}
