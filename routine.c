/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 11:50:03 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/07 20:31:44 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_philo *philo)
{
	if (is_simulation_over(philo))
		return ;
	pthread_mutex_lock(philo->left_fork);
	print_action(philo, "has taken a fork");
	if (philo->data->nb_philo == 1)
	{
		while (!is_simulation_over(philo))
			usleep(50);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	if (is_simulation_over(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	print_action(philo, "has taken a fork");
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->data->death_mutex);
	print_action(philo, "is eating");
	ft_usleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_lock(&philo->data->meals_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meals_mutex);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
