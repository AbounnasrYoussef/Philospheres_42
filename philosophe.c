/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 11:19:28 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/07 17:44:56 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_simulation_over(t_philo *philo)
{
	int	alive;

	pthread_mutex_lock(&philo->data->death_mutex);
	alive = philo->data->all_alive;
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (!alive);
}

static int	has_eaten_enough(t_philo *philo)
{
	int	done;

	done = 0;
	pthread_mutex_lock(&philo->data->meals_mutex);
	if (philo->data->nb_meals > 0
		&& philo->meals_eaten >= philo->data->nb_meals)
	{
		philo->data->philosophers_finished++;
		done = 1;
	}
	pthread_mutex_unlock(&philo->data->meals_mutex);
	return (done);
}

void	*philosopher(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(500);
	while (1)
	{
		if (philo->data->nb_philo != 1)
			print_action(philo, "is thinking");
		if (is_simulation_over(philo))
			break ;
		take_forks(philo);
		eat(philo);
		if (has_eaten_enough(philo))
			break ;
		print_action(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep, philo->data);
	}
	return (NULL);
}
