/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:12:55 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/08 09:51:14 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_printer(int x)
{
	if (x == 1)
	{
		printf("Usage: ./philo nb_philo time_to_die time_to_eat ");
		printf("time_to_sleep [nb_meals]\n");
	}
}

int	someone_died(t_data *data, int i)
{
	long	now;
	long	diff;

	now = get_time_in_ms();
	pthread_mutex_lock(&data->death_mutex);
	diff = now - data->philos[i].last_meal;
	if (diff > data->time_to_die && data->all_alive)
	{
		data->all_alive = 0;
		pthread_mutex_lock(&data->print_mutex);
		printf("%ld %d died\n", now - data->start_time, data->philos[i].id);
		pthread_mutex_unlock(&data->print_mutex);
		pthread_mutex_unlock(&data->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->death_mutex);
	return (0);
}

void	*monitor(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (1)
	{
		usleep(50);
		i = 0;
		while (i < data->nb_philo)
		{
			if (someone_died(data, i))
				return (NULL);
			i++;
		}
		pthread_mutex_lock(&data->meals_mutex);
		if (data->nb_meals > 0 && data->philosophers_finished == data->nb_philo)
		{
			data->all_alive = 0;
			pthread_mutex_unlock(&data->meals_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&data->meals_mutex);
	}
	return (NULL);
}

void	destroy_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_destroy(&data->meals_mutex);
	free(data->forks);
	free(data->philos);
}

int	main(int argc, char **argv)
{
	pthread_t	monitor_thread;
	t_data		data;
	int			i;

	i = 0;
	if (argc != 5 && argc != 6)
		return (ft_printer(1), 1);
	if (init_all(&data, argc, argv) != SUCCESS)
		return (printf("Initialization error.\n"), 1);
	while (i < data.nb_philo)
	{
		if (pthread_create(&data.philos[i].thread, NULL,
				philosopher, &data.philos[i]) != 0)
			return (ERROR);
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, monitor, &data) != 0)
		return (ERROR);
	i = 0;
	while (i < data.nb_philo)
		pthread_join(data.philos[i++].thread, NULL);
	pthread_join(monitor_thread, NULL);
	destroy_all(&data);
	return (0);
}
