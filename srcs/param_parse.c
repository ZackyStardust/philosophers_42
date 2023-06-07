/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpereira <fpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:50:28 by fpereira          #+#    #+#             */
/*   Updated: 2023/06/05 16:53:02 by fpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	check_args(char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if ((argv[i][j] < '0' || argv[i][j] > '9') && j != 0)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	param_parse(t_const_philo *var, char **argv)
{
	if (check_args(argv))
		return (error_msg());
	var->total_ate = 0;
	var->num_philo = ft_atoi(argv[1]);
	var->time_die = ft_atoi(argv[2]);
	var->time_eat = ft_atoi(argv[3]);
	var->time_sleep = ft_atoi(argv[4]);
	var->time = get_time();
	var->end = 0;
	if (var->num_philo <= 0 || var->time_die <= 0
		|| var->time_eat <= 0 || var->time_sleep <= 0)
		return (1);
	if (argv[5])
	{
		var->must_eat = ft_atoi(argv[5]);
		if (var->must_eat <= 0)
			return (1);
	}
	else
		var->must_eat = -1;
	return (0);
}

static int	assign_param(t_philo *philo, t_const_philo *var,
					pthread_mutex_t dead, pthread_mutex_t pr)
{
	int				i;
	t_forks			*m;

	i = -1;
	var->print = pr;
	var->dead = dead;
	m = init_forks(philo, var);
	if (!m)
		return (1);
	while (++i < var->num_philo)
	{
		philo[i].ate = 0;
		philo[i].id = i + 1;
		philo[i].var = var;
		philo[i].status = THINKING;
	}
	var->f = m;
	return (0);
}

t_forks	*init_forks(t_philo *philo, t_const_philo *var)
{
	int				i;
	int				*in_use;
	pthread_mutex_t	*c;
	t_forks			*m;

	i = -1;
	m = malloc(sizeof(t_forks) * var->num_philo);
	c = malloc(sizeof(pthread_mutex_t) * var->num_philo);
	in_use = malloc(sizeof(int) * var->num_philo);
	if (!m || !c || !in_use)
		return (NULL);
	while (++i < var->num_philo)
	{
		m[i].c = &c[i];
		in_use[i] = 0;
		m[i].i = &in_use[i];
		if (pthread_mutex_init(&c[i], NULL))
		{
			free_params(philo, m, var);
			return (NULL);
		}
	}
	return (m);
}

int	init_philo(t_philo *philo, t_const_philo *var)
{
	pthread_mutex_t	pr;
	pthread_mutex_t	dead;

	if (!philo || !var)
		return (free_params(philo, 0, var));
	if (pthread_mutex_init(&pr, NULL)
		|| pthread_mutex_init(&dead, NULL))
		return (free_params(philo, 0, var));
	if (assign_param(philo, var, dead, pr))
	{
		if (var->f)
		{
			if (var->f->c)
				free(var->f->c);
			if (var->f->i)
				free(var->f->i);
			free (var->f);
			return (free_params(philo, 0, var));
		}
	}
	return (0);
}
