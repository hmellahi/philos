/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 17:17:51 by hmellahi          #+#    #+#             */
/*   Updated: 2021/10/03 19:58:23 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_3.h"

void	*routine(void *val)
{
	t_philo			*philo;
	int				j;
	sem_t			*forks;

	philo = val;
	forks = philo->state->forks;
	j = -1;
	while (philo->state->n_must_eat < 0 || ++j < philo->state->n_must_eat)
	{
		think(philo);
		take_forks(philo);
		eat(philo);
		throw_forks(forks);
		sleeps(philo);
	}
	return (0);
}

void	*checker(void *val)
{
	t_philo	*philo;
	int		n_must_eat;

	philo = (t_philo *)val;
	n_must_eat = philo->state->n_must_eat;
	while (1)
	{
		if (philo->status != EATING && get_time()
			> (philo->state->die_time + philo->last_time_eat))
			print_msg(PHILO_DIES, philo);
		if (n_must_eat > 0 && philo->eat_count >= n_must_eat)
			exit(0);
		usleep(10);
	}
	return (val);
}

void	clear_state(t_state	*state, t_philo *philos)
{
	free(philos);
	sem_close(state->forks);
	sem_close(state->print_sem);
	sem_close(state->waiter);
}

int	main(int ac, char *av[])
{
	t_state	state;
	t_philo	*philos;

	if (check_args(ac, av) == -1)
		return (-1);
	sem_unlink("print");
	state.print_sem = sem_open("print", O_CREAT, 0644, 1);
	sem_unlink("waiter");
	state.waiter = sem_open("waiter", O_CREAT, 0644, 1);
	init(ac, av, &state, &philos);
	clear_state(&state, philos);
	return (0);
}
