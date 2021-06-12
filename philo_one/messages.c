/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 16:23:49 by hmellahi          #+#    #+#             */
/*   Updated: 2021/06/12 20:05:26 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_0.h"
#include <string.h>

int	print_err(int msg_index)
{
	t_string	messages[4];

	messages[0] = "couldnt create a thread";
	messages[1] = "couldnt join a thread";
	messages[2] = "not valid args";
	messages[3] = "COULDNT_CREATE_PROCESS";
	printf("%s\n", messages[msg_index]);
	clear_state(NULL, NULL, NULL);
	return (-1);
}

void	*die_and_exit(t_philo *philo, void *val)
{
	print_msg(PHILO_DIES, philo);
	(void)val;
//
	// return (val);
	// pthread_detach(threads);
	exit(0);
}

void	print_msg(int msg_index, t_philo *philo)
{
	unsigned long	time_in_ms;

	time_in_ms = get_time() / 1000;
	pthread_mutex_lock(&philo->state->print_mutex);
	if (msg_index == PHILO_TAKES_FORK)
		printf("%lu %d has taken a fork\n", time_in_ms, philo->index + 1);
	else if (msg_index == PHILO_EATING)
		printf("%lu %d is eating\n", time_in_ms, philo->index + 1);
	else if (msg_index == PHILO_DIES)
	{
		printf("%lu %d died\n", time_in_ms, philo->index + 1);
		return ;
	}
	else if (msg_index == PHILO_THINKS)
		printf("%lu %d is thinking\n", time_in_ms, philo->index + 1);
	else if (msg_index == PHILO_SLEEPS)
		printf("%lu %d is sleeping\n", time_in_ms, philo->index + 1);
	pthread_mutex_unlock(&philo->state->print_mutex);
}
