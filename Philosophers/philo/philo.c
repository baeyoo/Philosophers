/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobrycki <mobrycki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 16:42:24 by mobrycki          #+#    #+#             */
/*   Updated: 2021/09/24 14:56:09 by mobrycki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	my_error(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	write(2, "Error: ", 7);
	write(2, str, len);
	write(2, "\n", 1);
	return (1);
}

void	print_action(t_global *global, int id, char *string)
{
	pthread_mutex_lock(&(global->writing));
	if (!(global->died))
	{
		printf("[%lli] ", ft_timestamp() - global->timestamp);
		printf("Philosopher {%i} ", id);
		printf("%s\n", string);
	}
	pthread_mutex_unlock(&(global->writing));
	return ;
}

void	*philo_famished(void *philo)
{
	t_philo		*philo_1;

	philo_1 = (t_philo *)philo;
	pthread_mutex_lock(&(philo_1->global->forks[philo_1->left_fork_id]));
	print_action(philo_1->global, philo_1->id, BLUE "has taken a fork" RESET);
	pthread_mutex_lock(&(philo_1->global->forks[philo_1->right_fork_id]));
	print_action(philo_1->global, philo_1->id, CYAN "has taken a fork" RESET);
	philo_1->fork_check = 1;
	return (0);
}

int	philo_eats(t_philo *philo, int *eat)
{
	pthread_t	philu;

	print_action(philo->global, philo->id, YELLOW "is thinking.." RESET);
	pthread_create(&philu, NULL, philo_famished, philo);
	while (philo->fork_check == 0 && philo->global->died == 0)
	{
		if ((ft_timestamp() - philo->last_meal) >= \
			(unsigned long)philo->global->time_death)
			return (wise_death(philo));
	}
	print_action(philo->global, philo->id, GREEN "is eating" RESET);
	philo->last_meal = ft_timestamp();
	smart_sleep(philo->global->time_eat, philo);
	pthread_mutex_unlock(&(philo->global->forks[philo->left_fork_id]));
	pthread_mutex_unlock(&(philo->global->forks[philo->right_fork_id]));
	philo->fork_check = 0;
	(*eat)++;
	if (*eat == philo->global->n_eat)
		return (0);
	print_action(philo->global, philo->id, MAGENTA "is sleeping zZzZ" RESET);
	smart_sleep(philo->global->time_sleep, philo);
	(philo->x_ate)++;
	return (0);
}

void	*philo_thread(void *philu)
{
	t_philo	*philo;
	int		k;

	k = 0;
	philo = (t_philo *)philu;
	if (philo->id % 2)
		usleep(300);
	philo->last_meal = ft_timestamp();
	while (!(philo->global->died) && ((philo->global->n_eat == -1) \
		|| k < philo->global->n_eat))
	{
		philo_eats(philo, &k);
	}
	return (0);
}
