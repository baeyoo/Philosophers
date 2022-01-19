/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobrycki <mobrycki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 15:23:35 by mobrycki          #+#    #+#             */
/*   Updated: 2021/09/24 14:41:59 by mobrycki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	ft_timestamp(void)
{
	struct timeval	time;
	unsigned long	timeu;

	gettimeofday(&time, NULL);
	timeu = ((time.tv_sec) * 1000 + (time.tv_usec) / 1000);
	return (timeu);
}

long long	timediff(long long past, long long pres)
{
	return (pres - past);
}

int	wise_death(t_philo *philo)
{
	pthread_mutex_lock(&(philo->global->muerto));
	if (philo->global->died)
	{
		pthread_mutex_unlock(&(philo->global->muerto));
		return (0);
	}
	philo->global->died = 1;
	pthread_mutex_unlock(&(philo->global->muerto));
	pthread_mutex_lock(&(philo->global->writing));
	printf("[%lli] ", ft_timestamp() - philo->global->timestamp);
	printf("Philosopher {%i}", philo->id);
	printf("%s died.. :( %s\n", MAGENTA, RESET);
	pthread_mutex_unlock(&(philo->global->writing));
	return (0);
}

int	smart_sleep(int t_sleep, t_philo *philo)
{
	unsigned long	sleep_end;

	sleep_end = ft_timestamp() + t_sleep;
	while (!(philo->global->died) && (ft_timestamp() < sleep_end))
	{
		if ((ft_timestamp() - philo->last_meal) >= \
			(unsigned long)philo->global->time_death)
			return (wise_death(philo));
		usleep(t_sleep);
	}
	return (1);
}

void	exit_launcher(t_global *global, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < global->n_philo)
		pthread_join(philo[i].thread_id, NULL);
	i = -1;
	while (++i < global->n_philo)
		pthread_mutex_destroy(&(global->forks[i]));
	pthread_mutex_destroy(&(global->writing));
	pthread_mutex_destroy(&(global->meal_check));
	pthread_mutex_destroy(&(global->muerto));
}
