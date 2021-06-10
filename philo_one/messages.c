/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 16:23:49 by hmellahi          #+#    #+#             */
/*   Updated: 2021/06/10 19:21:58 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_0.h"

void	print_err(int msg_index)
{
	t_string	messages[3];

	messages[0] = "couldnt create a thread";
	messages[1] = "couldnt join a thread";
	messages[2] = "not valid args";
	printf("%s\n", messages[msg_index]);
	exit(1);
}

extern unsigned long g_start;

unsigned long	get_curr_time(t_state *state)
{
	unsigned long	time_in_ms;

	gettimeofday(&state->current_time, NULL);
	time_in_ms = state->current_time.tv_usec
	/ 1000 + state->current_time.tv_sec * 1000;
	return (time_in_ms);
}

void	print_msg(int msg_index, t_philo *philo)
{
	unsigned long	time_in_ms;

	time_in_ms = get_curr_time(philo->state);
	if (msg_index == PHILO_TAKES_FORK)
		printf("%lu %d has taken a fork\n", time_in_ms, philo->index + 1);
	else if (msg_index == PHILO_EATING)
		printf("%lu %d is eating\n", time_in_ms, philo->index + 1);
	else if (msg_index == PHILO_DIES)
		printf("%lu %d died\n", time_in_ms, philo->index + 1);
	else if (msg_index == PHILO_THINKS)
		printf("%lu %d is thinking\n", time_in_ms, philo->index + 1);
	else if (msg_index == PHILO_SLEEPS)
		printf("%lu %d is sleeping\n", time_in_ms, philo->index + 1);
}

int	ft_atoi(const char *str)
{
	int	neg;
	int	i;
	int	num;

	i = 0;
	neg = 1;
	num = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	return (num * neg);
}
