/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martin <martin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 07:58:31 by martin            #+#    #+#             */
/*   Updated: 2026/03/21 17:59:00 by martin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


static void	error_parse(void)
{
	printf("Wrong format, please use like this: ./codexion ");
	printf("<number_of_coders> <time_to_burnout> <time_to_compile> ");
	printf("<time_to_debug> <time_to_refactor> ");
	printf("<number_of_compiles_required> <dongle_cooldown> <scheduler>");
}

static int	ft_fill_env(t_env *env, char **argv)
{
	env->nb_coders = ft_atoi(argv[1]);
	env->time_bo = ft_atoi(argv[2]);
	env->time_compile = ft_atoi(argv[3]);
	env->time_debug = ft_atoi(argv[4]);
	env->time_refract = ft_atoi(argv[5]);
	env->compile_req = ft_atoi(argv[6]);
	env->dongle_cd = ft_atoi(argv[7]);

	if (ft_strcmp(argv[8], "fifo") == 0)
		env->scheduler = 0;
	else
		env->scheduler = 1;

	return (0);
}

int	init_base_env(t_env *env, char **argv)
{
	if (ft_fill_env(env, argv) != 0)
		return (1);
	env->stop_sim = 0;
	if (pthread_mutex_init(&env->stop_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&env->log_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&env->stop_mutex);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_env	env;

	if (argc != 9)
		return (error_parse(), 1);
	if (check_value(argv) == 1)
		return (1);
	if (init_base_env(&env, argv) != 0)
		return (1);
	if (init_resources(&env) != 0)
	{
		pthread_mutex_destroy(&env.stop_mutex);
		pthread_mutex_destroy(&env.log_mutex);
		return (1);
	}
	env.start_time = get_time();
	if (launch_simulation(&env) != 0)
	{
		final_cleanup(&env);
		return (1);
	}
	final_cleanup(&env);
	return (0);
}

