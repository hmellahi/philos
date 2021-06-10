/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 17:17:51 by hmellahi          #+#    #+#             */
/*   Updated: 2021/06/10 22:00:52 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_3.h"

int		to_ms(float time)
{
	return (time * 1000);
}

void	ft_usleep(t_ul time)
{
    t_ul	start;

	start = get_curr_time();
	usleep(time - 20000);
	while ((get_curr_time() - start) < time);
}

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
		print_msg(PHILO_THINKS, philo);
		sem_wait(forks);
		print_msg(PHILO_TAKES_FORK, philo);
		sem_wait(forks);
		print_msg(PHILO_TAKES_FORK, philo);
		print_msg(PHILO_EATING, philo);
		philo->last_time_eat = get_curr_time();
		ft_usleep(to_ms(philo->state->eat_time));
		philo->eat_count++;
		sem_post(forks);
		sem_post(forks);
		print_msg(PHILO_SLEEPS, philo);
		ft_usleep(to_ms(philo->state->sleep_time));
	}
	return 0;
}

void	*checker(void *val)
{
	int	i;
	int	n;
	t_philo	*philo;
	int		full;
	int		n_must_eat;

	philo = (t_philo *)val;
	n_must_eat = philo->state->n_must_eat;
	while(1)
	{
		if ((get_curr_time() - philo->last_time_eat) >= philo->state->die_time)
		{
			print_msg(PHILO_DIES, philo);
			exit(12);
		}
		// printf("[%d | %d]\n", n_must_eat, philo->eat_count);
		if (n_must_eat > 0 && philo->eat_count >= n_must_eat)
			exit(25);
		usleep(100);
	}
	return (val);
}
// CHANGE
int		is_number(t_string str)
{
	while (*str)
	{
		if (*str < 48 && *str > 57)
			return (0);
		str++;
	}
	return (1);
}
// CHANGE
void	check_args(int ac, t_string	*av)
{
	int	i;

	if (ac != 5 && ac != 6)
		print_err(NOT_VALID_ARGS);
	i = -1;
	while (++i < ac)
		if (!is_number(av[i]))
			print_err(NOT_VALID_ARGS);
}

void		init_semaphore(sem_t **semaphore, t_state *state)
{
	// sem_unlink("forks");
	// *semaphore = sem_open("forks", O_CREAT, 0644, 4);
    // if (*semaphore == SEM_FAILED)
	// {
	// 	perror("sem_open failed");
	// 	exit(EXIT_FAILURE);
	// } 
}

void	init(int ac, char* av[], t_state *state, t_philo **philos) 
{
	int	i;

	check_args(ac, av);
	state->count = ft_atoi(av[1]);
	state->die_time = ft_atoi(av[2]);
	state->eat_time = ft_atoi(av[3]);
	state->sleep_time = ft_atoi(av[4]);
	sem_unlink("forks");
	state->forks = sem_open("forks", O_CREAT, 0644, state->count);
	//init_semaphore(&semaphore, state);
	if (ac == 6)
		state->n_must_eat = ft_atoi(av[5]);
	else
		state->n_must_eat = -1;
	*philos = malloc(sizeof(t_philo) * state->count);
	i = -1;
	while (++i < state->count)
	{
		(*philos)[i].state = state;
		(*philos)[i].index = i;
		(*philos)[i].eat_count = 0;
		(*philos)[i].last_time_eat = get_curr_time();
	}
}

void    clear_state(t_state	*state, t_philo *philos, sem_t *semaphore)
{
	int	i;
	int	n;

	n = state->count;
	free(philos);
	sem_close(semaphore);
}

int		spawn_proc(t_philo philo)
{
	pid_t	pid;
	pthread_t	threads[2];
	int		i;

	pid = fork();
	if (pid == -1)
		return (pid);
	if (pid == 0)
	{
		if (pthread_create(&threads[0], NULL, &routine, &philo) != 0)
			print_err(COULDNT_CREATE_THREAD);
		if (pthread_create(&threads[1], NULL, &checker,  &philo) != 0)
				print_err(COULDNT_CREATE_THREAD);
		i = -1;
		while (++i < 2)
			if (pthread_join(threads[i], NULL))
				print_err(COULDNT_CREATE_THREAD);
	}
	return (pid);
}

int		init_processes(t_state *state, t_philo *philos)
{
	int	i;
	int status;
	int	exit_status;

	i = -1;
	while (++i < state->count)
		if ((philos[i].pid = spawn_proc(philos[i])) == -1)
			print_err(COULDNT_CREATE_PROCESS);
	// while (waitpid(-1, &wstatus, 0) != -1);
	// // puts();
	// if (WIFEXITED(wstatus))
	// {
	// 	int exit_value = WEXITSTATUS(wstatus);
	// 	printf("process exited with : %d \n", exit_value);
	// 	if (exit_value == 120)
	// 	{
	// 		i = -1;
	// 		while (++i < state->count)
	// 		{
	// 			printf("process killed : %d \n", philos[i].pid);
	// 			kill(philos[i].pid, SIGKILL);
	// 		}
	// 	}
	// }
	i = -1;
	while (++i < state->count)
	{
		waitpid(philos[i].pid, &status, 0);
		exit_status = WEXITSTATUS(status);
		// printf("process exited with : %d|%d \n", i,exit_status);
		if (exit_status == 12)
		{
			i = -1;
			while (++i < state->count)
			{
				printf("process killed : %d \n", philos[i].pid);
				kill(philos[i].pid, SIGKILL);
			}
		}
	}
	return 1;
}
int main(int ac, char* av[])
{
	t_state	state;
	t_philo *philos;

    // if (semaphore == SEM_FAILED)
	// {
	// 	perror("sem_open failed");
	// 	exit(EXIT_FAILURE);
	// }
	sem_unlink("print");
	state.print_sem = sem_open("print", O_CREAT, 0644, 1);
	init(ac, av, &state, &philos);
	// clear_state(&state, philos, semaphore);
	init_processes(&state, philos);
	// sem_close(semaphore);
	return 0;
}