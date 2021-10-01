/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_circle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 23:57:44 by hamza             #+#    #+#             */
/*   Updated: 2021/10/01 18:45:26 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_0.h"

void	eat(t_philo *philo)
{
	philo->last_time_eat = get_time();
	print_msg(PHILO_EATING, philo);
	ft_usleep(philo->state->eat_time);
	philo->eat_count++;
}

void	take_forks(t_philo *philo, pthread_mutex_t *forks)
{
	pthread_mutex_lock(&forks[philo->index % philo->state->count]);
	print_msg(PHILO_TAKES_FORK, philo);
	pthread_mutex_lock(&forks[(philo->index + 1) % philo->state->count]);
	print_msg(PHILO_TAKES_FORK, philo);
	philo->status = EATING;
}

void	sleeps(t_philo *philo)
{
	philo->status = SLEEPING;
	print_msg(PHILO_SLEEPS, philo);
	ft_usleep(philo->state->sleep_time);
}

void	throw_forks(t_philo *philo, pthread_mutex_t *forks)
{
	pthread_mutex_unlock(&forks[philo->index]);
	pthread_mutex_unlock(&forks[(philo->index + 1) % philo->state->count]);
}

void	think(t_philo *philo)
{
	print_msg(PHILO_THINKS, philo);
	philo->status = THINKING;
}
