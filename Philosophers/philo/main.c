/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobrycki <mobrycki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 12:44:31 by mobrycki          #+#    #+#             */
/*   Updated: 2021/09/24 14:59:27 by mobrycki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philo.h"

int	init_philo(t_philo *philu, t_global *global)
{
	int	i;

	i = 0;
	while (i < global->n_philo)
	{
		philu[i].id = i + 1;
		philu[i].x_ate = 0;
		philu[i].left_fork_id = i;
		philu[i].right_fork_id = (i + 1);
		if ((i + 1) == global->n_philo)
			philu[i].right_fork_id = 0;
		philu[i].last_meal = 0;
		philu[i].global = global;
		philu[i].fork_check = 0;
		i++;
	}
	return (0);
}

int	mutex_init(t_global *global)
{
	int	i;

	i = global->n_philo;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(global->forks[i]), NULL))
			return (1);
	}
	if (pthread_mutex_init(&(global->writing), NULL))
		return (1);
	if (pthread_mutex_init(&(global->meal_check), NULL))
		return (1);
	if (pthread_mutex_init(&(global->muerto), NULL))
		return (1);
	return (0);
}

int	init_all(t_global *global, char **argv)
{
	global->n_philo = ft_atoi(argv[1]);
	global->time_death = ft_atoi(argv[2]);
	global->time_eat = ft_atoi(argv[3]);
	global->time_sleep = ft_atoi(argv[4]);
	global->all_ate = 0;
	global->died = 0;
	if (global->n_philo < 1 || global->time_death < 0 || global->time_eat < 0
		|| global->time_sleep < 0 || global->n_philo > 200)
		return (1);
	if (argv[5])
	{
		global->n_eat = ft_atoi(argv[5]);
		if (global->n_eat <= 0)
			return (1);
	}
	else
		global->n_eat = -1;
	if (mutex_init(global))
		return (2);
	return (0);
}

int	execute(t_global *global)
{
	int			i;
	pthread_t	phil[200];
	t_philo		philu[200];

	i = 0;
	init_philo(philu, global);
	global->timestamp = ft_timestamp();
	while (i < global->n_philo)
	{
		pthread_create(&phil[i], NULL, philo_thread, &philu[i]);
		i++;
	}
	i = 0;
	while (i < global->n_philo)
	{
		pthread_join(phil[i], NULL);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_global	global;
	int			ret;

	ret = 0;
	if (argc < 5 || argc > 6)
		return (my_error("Wrong number of arguments!"));
	ret = init_all(&global, argv);
	if (ret || check_init(argv) == 0)
	{
		my_error("Invalid arguments!");
		exit (1);
	}
	if (execute(&global))
		my_error("Encountered an error during mutex creation");
	return (0);
}
