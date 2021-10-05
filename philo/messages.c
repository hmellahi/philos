/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 16:23:49 by hmellahi          #+#    #+#             */
/*   Updated: 2021/10/05 18:17:23 by hmellahi         ###   ########.fr       */
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
	return (-1);
}

int	print_msg(int msg_index, t_philo *philo)
{
	t_ul	time_in_ms;

	time_in_ms = get_time() - philo->state->start_time;
	pthread_mutex_lock(&philo->state->print_mutex);
	if (msg_index == PHILO_TAKES_FORK)
		printf("%llu %d has taken a fork\n", time_in_ms, philo->index + 1);
	else if (msg_index == PHILO_EATING)
		printf("%llu %d is eating\n", time_in_ms, philo->index + 1);
	else if (msg_index == PHILO_DIES)
	{
		pthread_mutex_lock(&philo->eat_mutex);
		printf("%llu %d died\n", time_in_ms, philo->index + 1);
		return (-1);
	}
	else if (msg_index == PHILO_THINKS)
		printf("%llu %d is thinking\n", time_in_ms, philo->index + 1);
	else if (msg_index == PHILO_SLEEPS)
		printf("%llu %d is sleeping\n", time_in_ms, philo->index + 1);
	pthread_mutex_unlock(&philo->state->print_mutex);
	return (0);
}
