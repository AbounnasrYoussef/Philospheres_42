/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 11:41:28 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/07 19:59:14 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_action(t_philo *philo, char *action)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->all_alive)
	{
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%ld %d %s\n",
			get_time_in_ms() - philo->data->start_time, philo->id, action);
		pthread_mutex_unlock(&philo->data->print_mutex);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
}

long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(long time_in_ms, t_data *data)
{
	long	start;

	start = get_time_in_ms();
	while (get_time_in_ms() - start < time_in_ms)
	{
		pthread_mutex_lock(&data->death_mutex);
		if (!data->all_alive)
		{
			pthread_mutex_unlock(&data->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->death_mutex);
		usleep(100);
	}
}
