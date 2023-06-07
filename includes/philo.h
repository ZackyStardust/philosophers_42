/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpereira <fpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 19:12:53 by fpereira          #+#    #+#             */
/*   Updated: 2023/06/05 16:53:34 by fpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define EATING		1
# define SLEEPING	2
# define THINKING	3

typedef struct s_fork
{
	int				*i;
	pthread_mutex_t	*c;
}	t_forks;

typedef struct s_const_philo
{
	int				num_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat;
	int				total_ate;
	unsigned long	time;
	int				end;
	pthread_mutex_t	print;
	pthread_mutex_t	dead;
	t_forks			*f;
}t_const_philo;

typedef struct s_philo
{
	int				ate;
	int				id;
	int				status;
	t_const_philo	*var;
	pthread_mutex_t	*mutex;
	unsigned long	last_meal;
}t_philo;

int				error_msg(void);
int				print(t_philo *philo, char *action);
void			kill_philo(t_philo *philo, t_const_philo *var);
void			*take_action(void *p);
int				check_args(char **argv);
int				param_parse(t_const_philo *var, char **argv);
void			assign_params(t_philo *philo, t_const_philo *var,
					pthread_mutex_t *m, pthread_mutex_t *pr);
int				free_params(t_philo *philo, t_forks *m, t_const_philo *var);
int				init_philo(t_philo *philo, t_const_philo *var);
int				ft_atoi(const char *str);
void			dest_mutex(t_philo *philo);
unsigned long	get_time(void);
unsigned long	current_time(t_philo *philo);
t_forks			*init_forks(t_philo *philo, t_const_philo *var);
void			philo_eat(t_philo *philo);
void			take_forks(t_philo *philo);
void			philo_sleep(t_philo *philo);
void			destroy_all(t_philo *philo, t_const_philo *var, pthread_t *th);
void			ft_usleep(t_philo *philo, int time);
int				philo_dead(t_philo *philo);
int				all_ate(t_philo *philo, t_const_philo *var);
void			thread_create_destroy(t_const_philo	*var, t_philo *philo,
					pthread_t *th, char **argv);
int				all_ate_loop(t_const_philo *var, t_philo *philo);

#endif