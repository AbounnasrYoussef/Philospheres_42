/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:08:05 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/07 16:50:58 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define SUCCESS 0
# define ERROR 1

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	long			last_meal;
	int				meals_eaten;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}					t_philo;

typedef struct s_data
{
	int				nb_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				nb_meals;
	int				all_alive;
	int				philosophers_finished;
	long			start_time;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	meals_mutex;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}					t_data;

int		someone_died(t_data *data, int i);
int		init_all(t_data *data, int argc, char **argv);
int		init_mutexes(t_data *data);
void	init_philos(t_data *data);
void	*monitor(void *arg);
void	ft_usleep(long time_in_ms, t_data *data);
long	get_time_in_ms(void);
void	destroy_all(t_data *data);
void	*philosopher(void *arg);
void	eat(t_philo *philo);
void	take_forks(t_philo *philo);
int		ft_atoi(const char *str);
void	print_action(t_philo *philo, char *action);
long	ft_atol(const char *str);
int		ft_isdigit(int c);
int		is_simulation_over(t_philo *philo);

#endif
