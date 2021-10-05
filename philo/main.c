/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 19:01:10 by hmellahi          #+#    #+#             */
/*   Updated: 2021/10/05 18:08:13 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_0.h"

void	*routine(void *val)
{
	t_philo			*philo;
	pthread_mutex_t	*forks;
	int				j;

	j = -1;
	philo = val;
	forks = philo->state->forks;
	while (philo->state->n_must_eat < 0 || ++j < philo->state->n_must_eat)
	{
		think(philo);
		take_forks(philo, forks);
		eat(philo);
		throw_forks(philo, forks);
		sleeps(philo);
	}
	return (0);
}

int	checker(t_philo *philos)
{
	int		i;
	int		full;
	t_state	*state;

	state = philos[0].state;
	while (1)
	{
		full = 0;
		i = -1;
		while (++i < state->count)
		{
			if (philos[i].status != EATING && (get_time()
					- philos[i].last_time_eat) > state->die_time)
				return (print_msg(PHILO_DIES, &philos[i]));
			if (state->n_must_eat > 0 && philos[i].eat_count
				>= state->n_must_eat)
				full++;
		}
		if (full == state->count)
			return (0);
		usleep(10);
	}
	return (0);
}

void	clear_state( t_state	*state, t_philo *philos, pthread_t *threads)
{
	int	i;
	int	n;

	if (!state)
		return ;
	i = -1;
	n = state->count;
	pthread_mutex_destroy(&state->print_mutex);
	while (++i < n)
		pthread_mutex_destroy(&state->forks[i]);
	if (state)
		free(state->forks);
	if (philos)
	{
		free(philos);
		i = -1;
		while (++i < n)
			pthread_mutex_destroy(&philos[i].eat_mutex);
	}
	if (threads)
		free(threads);
}

pthread_t	*init_threads(t_state *state, t_philo *philos)
{
	int			i;
	int			n;
	pthread_t	*threads;

	n = state->count;
	threads = malloc(sizeof(pthread_t) * n);
	i = -1;
	while (++i < state->count)
	{
		if (pthread_create(&threads[i], NULL, &routine, &philos[i]) != 0)
		{
			print_err(COULDNT_CREATE_THREAD);
			return (threads);
		}
		usleep(100);
	}
	i = -1;
	checker(philos);
	return (threads);
}

int	main(int ac, char *av[])
{
	t_state		state;
	t_philo		*philos;
	pthread_t	*threads;

	if (check_args(ac, av) == -1)
		return (-1);
	init(ac, av, &state, &philos);
	if (!state.n_must_eat)
	{
		clear_state(&state, philos, NULL);
		return (0);
	}
	threads = init_threads(&state, philos);
	clear_state(&state, philos, threads);
	return (0);
}
