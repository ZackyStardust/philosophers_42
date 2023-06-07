/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints_exits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpereira <fpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:51:34 by fpereira          #+#    #+#             */
/*   Updated: 2023/06/05 16:51:32 by fpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	error_msg(void)
{
	printf("Error: Wrong number of parameters. Please, use as following:\n");
	printf("./philo <num of philo> <time to die> <time to eat> <time to sleep> \
<number of times to eat (optional)>\n");
	return (1);
}

int	print(t_philo *philo, char *action)
{
	pthread_mutex_lock(&philo->var->print);
	if (!philo_dead(philo))
		printf("%lu	%d %s\n", current_time(philo), philo->id, action);
	pthread_mutex_unlock(&philo->var->print);
	return (0);
}

int	free_params(t_philo *philo, t_forks *m, t_const_philo *var)
{
	if (philo)
		free(philo);
	if (m)
	{
		if (m->c)
			free(m->c);
		if (m->i)
			free(m->i);
		free(m);
	}
	if (var)
		free(var);
	return (1);
}

void	destroy_all(t_philo *philo, t_const_philo *var, pthread_t *th)
{
	dest_mutex(philo);
	free_params(philo, philo->var->f, var);
	free(th);
}

void	dest_mutex(t_philo *philo)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&philo->var->dead);
	pthread_mutex_destroy(&philo->var->print);
	while (++i < philo->var->num_philo)
		pthread_mutex_destroy(&philo->var->f->c[i]);
}
