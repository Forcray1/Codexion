/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martin <martin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 08:53:04 by martin            #+#    #+#             */
/*   Updated: 2026/03/21 17:21:12 by martin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_request
{
	int				coder_id;
	long long		priority_value;
}	t_request;

typedef struct s_queue
{
	t_request		*requests;
	int				size;
	int				capacity;
}	t_queue;

typedef struct s_env
{
	int				nb_coders;
	int				time_bo;
	int				time_compile;
	int				time_debug;
	int				time_refract;
	int				compile_req;
	int				dongle_cd;
	int				scheduler;

	long long		start_time;
	int				stop_sim;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	log_mutex;

	struct t_coder	*coders;
	struct s_dongle	*dongles;
}	t_env;

typedef struct s_dongle
{
	int				id;
	int				is_used;
	long long		available_at;
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	t_queue			wait_queue;

}	t_dongle;

typedef struct s_coder
{
	int				id;
	pthread_t		thread;
	long long		last_compile;
	int				nb_compile;
	int				is_done;
	struct s_dongle	*left_dongle;
	struct s_dongle	*right_dongle;
	struct s_env	*env;
}	t_coder;

int			main(int argc, char **argv);

int			check_value(char **argv);

int			init_resources(struct s_env *env);

int			launch_simulation(struct s_env *env);

void		final_cleanup(t_env *env);

int			ft_strcmp(char *s1, char *s2);
int			ft_atoi(char *str);
long long	get_time(void);

#endif