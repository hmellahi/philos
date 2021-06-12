/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 23:41:44 by hamza             #+#    #+#             */
/*   Updated: 2021/06/12 00:22:23 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_0.h"

int		is_number(t_string str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

int		check_args(int ac, t_string	*av)
{
	int	i;

	if (ac != 5 && ac != 6)
		return (print_err(NOT_VALID_ARGS));
	i = 0;
	while (++i < ac)
		if (!is_number(av[i]) || ft_atoi(av[i]) < 0)
			return (print_err(NOT_VALID_ARGS));
	return (0);
}


void	init_state(t_state *state, t_string *av, int ac)
{
	state->count = ft_atoi(av[1]);
	state->die_time = ft_atoi(av[2]) * 1000;
	state->eat_time = ft_atoi(av[3]) * 1000;
	state->sleep_time = ft_atoi(av[4]) * 1000;
	if (ac == 6)
		state->n_must_eat = ft_atoi(av[5]);
	else
		state->n_must_eat = -1;
	state->forks = malloc(sizeof(pthread_mutex_t) * state->count);
}

void	init(int ac, char* av[], t_state *state, t_philo **philos) 
{
	int	i;

	init_state(state, av, ac);
	pthread_mutex_init(&state->print_mutex, NULL);
	i = -1;
	while (++i < state->count)
		pthread_mutex_init(&state->forks[i], NULL);
	*philos = malloc(sizeof(t_philo) * state->count);
	i = -1;
	while (++i < state->count)
	{
		(*philos)[i].state = state;
		(*philos)[i].status = THINKING;
		(*philos)[i].l_fork = -1;
		(*philos)[i].r_fork = -1;
		(*philos)[i].index = i;
		(*philos)[i].eat_count = 0;
		(*philos)[i].last_time_eat = state->start_time;
	}
}