/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_ate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpereira <fpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:56:35 by fpereira          #+#    #+#             */
/*   Updated: 2023/06/05 15:14:39 by fpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	all_ate(t_philo *philo, t_const_philo *var)
{
	int	trigger;

	trigger = all_ate_loop(var, philo);
	if (trigger == 1)
	{
		pthread_mutex_lock(&var->dead);
		var->end++;
		pthread_mutex_unlock(&var->dead);
		return (1);
	}
	else if (trigger == -1)
		return (1);
	return (0);
}

int	all_ate_loop(t_const_philo *var, t_philo *philo)
{
	int	i;
	int	trigger;

	i = -1;
	while (++i < var->num_philo)
	{
		pthread_mutex_lock(&var->dead);
		if (philo[i].ate == var->must_eat)
			trigger = 1;
		else if (var->end == 1)
		{
			trigger = -1;
			pthread_mutex_unlock(&var->dead);
			break ;
		}
		else
		{
			pthread_mutex_unlock(&var->dead);
			trigger = 0;
			break ;
		}
		pthread_mutex_unlock(&var->dead);
	}	
	return (trigger);
}

void	thread_create_destroy(t_const_philo	*var, t_philo *philo,
								pthread_t *th, char **argv)
{
	int	i;

	i = -1;
	while (++i < philo->var->num_philo)
	{
		pthread_create(&th[i], NULL, take_action, philo + i);
		usleep (100);
	}
	i = -1;
	if (argv[5])
		while (1)
			if (all_ate(philo, var) == 1)
				break ;
	while (++i < philo->var->num_philo)
		pthread_join(th[i], NULL);
	destroy_all(philo, var, th);
}
