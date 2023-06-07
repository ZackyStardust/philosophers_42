/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpereira <fpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 19:20:24 by fpereira          #+#    #+#             */
/*   Updated: 2023/06/05 16:51:56 by fpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	ft_atoi(const char *str)
{
	long int		ret;
	size_t	i;
	long int		sign;

	ret = 0;
	i = 0;
	sign = 1;
	if (!str[0] || !str)
		return (0);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign *= -1;
	if (str[i] == '+' || str[i] == '-')
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
		ret = (ret * 10) + (str[i++] - 48);
	if (ret * sign > 2147483647 || ret * sign < -2147483648)
		return (-1);
	return (ret * sign);
}

unsigned long	get_time(void)
{
	struct timeval	time;
	unsigned long	l;
	unsigned long	s;
	unsigned long	u;

	gettimeofday(&time, NULL);
	s = (time.tv_sec * 1000);
	u = (time.tv_usec / 1000);
	l = s + u;
	return (l);
}

unsigned long	current_time(t_philo *philo)
{
	return (get_time() - philo->var->time);
}

void	philo_sleep(t_philo *philo)
{
		pthread_mutex_lock(&philo->var->dead);
		if (philo->var->end == 0)
		{
			pthread_mutex_unlock(&philo->var->dead);
			print(philo, "is sleeping");
			ft_usleep(philo, philo->var->time_sleep);
			philo->status = SLEEPING;
		}
		else
			pthread_mutex_unlock(&philo->var->dead);
}

void	ft_usleep(t_philo *philo, int time)
{
	unsigned long	start;

	start = get_time();
	while (!philo_dead(philo))
		if (get_time() - start > (unsigned long)time)
			break ;
}
