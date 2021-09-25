/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_circle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 23:57:44 by hamza             #+#    #+#             */
/*   Updated: 2021/06/12 19:43:42 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_3.h"

void	eat(t_philo *philo)
{
	philo->status = EATING;
	print_msg(PHILO_EATING, philo);
	philo->last_time_eat = get_time();
	ft_usleep(philo->state->eat_time);
	philo->eat_count++;
}

void	take_forks(t_philo *philo)
{
	sem_wait(philo->state->waiter);
	sem_wait(philo->state->forks);
	print_msg(PHILO_TAKES_FORK, philo);
	sem_wait(philo->state->forks);
	print_msg(PHILO_TAKES_FORK, philo);
	sem_post(philo->state->waiter);
}

void	sleeps(t_philo *philo)
{
	philo->status = SLEEPING;
	print_msg(PHILO_SLEEPS, philo);
	ft_usleep(philo->state->sleep_time);
}

void	throw_forks(sem_t *forks)
{
	sem_post(forks);
	sem_post(forks);
}

void	think(t_philo *philo)
{
	print_msg(PHILO_THINKS, philo);
	philo->status = THINKING;
}
