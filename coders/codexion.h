/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martin <martin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 08:53:04 by martin            #+#    #+#             */
/*   Updated: 2026/03/22 14:54:55 by martin           ###   ########.fr       */
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

struct						s_env;
struct						s_dongle;
struct						s_coder;

typedef struct s_request	t_request;
typedef struct s_env		t_env;
typedef struct s_dongle		t_dongle;
typedef struct s_coder		t_coder;

struct s_request
{
	int			coder_id;
	long long	priority_val;
};

struct s_coder
{
	int				id;
	int				nb_compiles;
	long long		last_compile_start;
	t_env			*env;
	t_dongle		*left_dongle;
	t_dongle		*right_dongle;
	pthread_t		thread;
};

struct s_dongle
{
	int				id;
	int				is_used;
	long long		last_use;
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	struct s_wait_queue
	{
		t_request	*requests;
		int			size;
	}	wait_queue;
};

struct s_env
{
	int				nb_coders;
	int				time_bo;
	int				time_compile;
	int				time_debug;
	int				time_refract;
	int				compile_req;
	int				dongle_cd;
	int				scheduler;
	int				stop_sim;
	long long		start_time;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	log_mutex;
	t_coder			*coders;
	t_dongle		*dongles;
};

int			main(int argc, char **argv);

int			check_value(char **argv);

int			init_resources(struct s_env *env);

int			launch_simulation(struct s_env *env);

void		*monitor_routine(void *arg);

void		final_cleanup(t_env *env);

int			ft_strcmp(char *s1, char *s2);
int			ft_atoi(char *str);
long long	get_time(void);
void		action_sleep(long long duration, t_env *env);
int			check_stop(t_env *env);
void		print_status(t_coder *coder, char *status);
void		wait_for_start(t_env *env);
int			must_stop(t_env *env);

#endif