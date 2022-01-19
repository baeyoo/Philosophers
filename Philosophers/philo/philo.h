/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobrycki <mobrycki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 16:42:29 by mobrycki          #+#    #+#             */
/*   Updated: 2021/09/24 12:45:56 by mobrycki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <signal.h>

# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define YELLOW  "\033[0;33m"
# define BLUE    "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN    "\x1b[36m"
# define RESET   "\x1b[0m"

typedef struct s_philo
{
	int					id;
	int					x_ate;
	int					left_fork_id;
	int					right_fork_id;
	int					fork_check;
	long long			last_meal;
	struct s_global		*global;
	pthread_t			thread_id;
}				t_philo;

typedef struct s_global
{
	int					n_philo;
	int					time_death;
	int					time_eat;
	int					time_sleep;
	int					all_ate;
	int					n_eat;
	int					died;
	int					num;
	long long			timestamp;
	pthread_mutex_t		meal_check;
	pthread_mutex_t		forks[250];
	pthread_mutex_t		writing;
	pthread_mutex_t		muerto;
	t_philo				philo[200];
}				t_global;

int				ft_number(char *n);
int				ft_atoi(const char *str);
int				check_init(char **argv);
int				init_all(t_global *global, char **argv);
int				init_philo(t_philo *philu, t_global *global);
int				my_error(char *str);
int				wise_death(t_philo *philo);
int				smart_sleep(int t_sleep, t_philo *philo);
void			exit_launcher(t_global *global, t_philo *philo);
int				mutex_init(t_global *global);
void			*philo_thread(void *philoso);
void			print_action(t_global *global, int id, char *string);
int				execute(t_global *global);
int				philo_eats(t_philo *philo, int *eat);
long long		timediff(long long past, long long pres);
unsigned long	ft_timestamp(void);

#endif