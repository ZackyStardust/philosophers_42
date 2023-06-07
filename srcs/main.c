/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpereira <fpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:50:25 by fpereira          #+#    #+#             */
/*   Updated: 2023/06/05 16:55:48 by fpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>	

int	philo_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->var->dead);
	if (philo->var->end >= 1)
	{
		pthread_mutex_unlock(&philo->var->dead);
		return (1);
	}
	if (get_time() - philo->last_meal
		> (unsigned long)philo->var->time_die)
	{
		philo->var->end++;
		printf("%lu	%d died\n", current_time(philo), philo->id);
		pthread_mutex_unlock(&philo->var->dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->var->dead);
	return (0);
}

void	take_forks(t_philo	*p)
{
	while (!philo_dead(p))
	{
		pthread_mutex_lock(p->var->f[p->id - 1].c);
		if (*(p->var->f[p->id - 1].i) == 0)
		{
			*(p->var->f[p->id - 1].i) = 1;
			pthread_mutex_unlock(p->var->f[p->id - 1].c);
			break ;
		}
		pthread_mutex_unlock(p->var->f[p->id - 1].c);
	}
	print(p, "has taken a fork");
	while (!philo_dead(p))
	{
		pthread_mutex_lock(p->var->f[p->id % p->var->num_philo].c);
		if (*(p->var->f[p->id % p->var->num_philo].i) == 0)
		{
			*(p->var->f[p->id % p->var->num_philo].i) = 1;
			pthread_mutex_unlock(p->var->f[p->id % p->var->num_philo].c);
			break ;
		}
		pthread_mutex_unlock(p->var->f[p->id % p->var->num_philo].c);
	}
	print(p, "has taken a fork");
}

void	philo_eat(t_philo *philo)
{
	take_forks(philo);
	print(philo, "is eating");
	pthread_mutex_lock(&philo->var->dead);
	philo->ate++;
	pthread_mutex_unlock(&philo->var->dead);
	ft_usleep(philo, philo->var->time_eat);
	pthread_mutex_lock(philo->var->f[philo->id - 1].c);
	*(philo->var->f[philo->id - 1].i) = 0;
	pthread_mutex_unlock(philo->var->f[philo->id - 1].c);
	pthread_mutex_lock(philo->var->f[philo->id % philo->var->num_philo].c);
	*(philo->var->f[philo->id % philo->var->num_philo].i) = 0;
	pthread_mutex_unlock(philo->var->f[philo->id % philo->var->num_philo].c);
	pthread_mutex_lock(&philo->var->dead);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->var->dead);
	philo->status = EATING;
}

void	*take_action(void *p)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)p;
	if (philo->var->num_philo >= 100)
		i = (philo->var->must_eat * 1000) / 2;
	else
		i = 1000;
	if (philo->id % 2 == 0)
		usleep(i);
	philo->last_meal = get_time();
	while (philo->ate != philo->var->must_eat && !philo_dead(philo))
	{
		if (!philo_dead(philo) && philo->status == THINKING)
			philo_eat(philo);
		if (!philo_dead(philo) && philo->status == EATING)
			philo_sleep(philo);
		if (!philo_dead(philo) && philo->status == SLEEPING)
			philo->status = print(philo, "is thinking") + THINKING;
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_const_philo	*var;
	t_philo			*philo;
	pthread_t		*th;

	if (argc < 5 || argc > 6)
		return (error_msg());
	var = (t_const_philo *)malloc(sizeof(t_const_philo));
	if (param_parse(var, argv))
		return (free_params(0, 0, var));
	philo = (t_philo *)malloc(sizeof(t_philo) * var->num_philo);
	if (init_philo(philo, var))
		return (1);
	th = (pthread_t *)malloc(sizeof(pthread_t) * var->num_philo);
	thread_create_destroy(var, philo, th, argv);
	return (0);
}
