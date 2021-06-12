/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 02:59:43 by hamza             #+#    #+#             */
/*   Updated: 2021/06/12 19:43:42 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_3.h"

int	spawn_proc(t_philo philo)
{
	pid_t		pid;
	pthread_t	threads[2];
	int			i;

	pid = fork();
	if (pid == -1)
		return (pid);
	if (pid == 0)
	{
		if (pthread_create(&threads[0], NULL, &routine, &philo) != 0)
			print_err(COULDNT_CREATE_THREAD);
		if (pthread_create(&threads[1], NULL, &checker, &philo) != 0)
			print_err(COULDNT_CREATE_THREAD);
		i = -1;
		while (++i < 2)
			if (pthread_join(threads[i], NULL))
				print_err(COULDNT_CREATE_THREAD);
	}
	return (pid);
}

int	init_processes(t_state *state, t_philo *philos)
{
	int	i;
	int	status;
	int	exit_status;
	int	j;

	i = -1;
	while (++i < state->count)
	{
		philos[i].pid = spawn_proc(philos[i]);
		if (philos[i].pid == -1)
			return (print_err(COULDNT_CREATE_PROCESS));
	}
	j = -1;
	while (++j < state->count)
	{
		waitpid(-1, &status, 0);
		exit_status = WEXITSTATUS(status);
		if (exit_status == DIE_STATUS_CODE)
		{
			i = -1;
			while (++i < state->count)
				kill(philos[i].pid, SIGKILL);
		}
	}
	return (1);
}

void	init_state(t_state *state, t_string *av, int ac)
{
	state->count = ft_atoi(av[1]);
	state->die_time = ft_atoi(av[2]) * 1000;
	state->eat_time = ft_atoi(av[3]) * 1000;
	state->sleep_time = ft_atoi(av[4]) * 1000;
	state->start = get_time();
	if (ac == 6)
		state->n_must_eat = ft_atoi(av[5]);
	else
		state->n_must_eat = -1;
	sem_unlink("forks");
	state->forks = sem_open("forks", O_CREAT, 0644, state->count);
}

void	init(int ac, char **av, t_state *state, t_philo **philos)
{
	int	i;

	init_state(state, av, ac);
	*philos = malloc(sizeof(t_philo) * state->count);
	i = -1;
	while (++i < state->count)
	{
		(*philos)[i].state = state;
		(*philos)[i].index = i;
		(*philos)[i].eat_count = 0;
		(*philos)[i].last_time_eat = state->start;
		(*philos)[i].status = THINKING;
	}
	init_processes(state, *philos);
}
