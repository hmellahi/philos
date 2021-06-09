/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 17:17:51 by hmellahi          #+#    #+#             */
/*   Updated: 2021/06/09 21:58:49 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_3.h"

int		to_ms(float time, int i)
{
	return (time * 1000);
}

void	*routine(void *val)
{
	t_philo			*philo;
	pthread_mutex_t *forks;
	int				i;
	int				n;
	float			sleep_time;

	philo = val;
	forks = philo->state->forks;
	sleep_time = philo->state->sleep_time;
	i = philo->index;
	n = philo->state->count;
	int j = -1;
	philo->semaphore = sem_open("forks", 0);
	while (philo->state->n_must_eat < 0 || ++j < philo->state->n_must_eat)
	{
		print_msg(PHILO_THINKS, philo);
		philo->last_time_eat = get_curr_time(philo->state);
		sem_wait(philo->semaphore);
		sem_wait(philo->semaphore);
		philo->eat_count++;
		print_msg(PHILO_TAKES_FORK, philo);
		print_msg(PHILO_TAKES_FORK, philo);
		print_msg(PHILO_EATING, philo);
		usleep(to_ms(philo->state->eat_time, 0));
		sem_post(philo->semaphore);
		sem_post(philo->semaphore);
		print_msg(PHILO_SLEEPS, philo);
		usleep(to_ms(philo->state->sleep_time, 0));
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
		if ((get_curr_time(philo->state) - philo->last_time_eat) >= philo->state->die_time)
		{
			print_msg(PHILO_DIES, philo);
			exit(120);
		}
		// printf("[%d | %d]\n", n_must_eat, philo->eat_count);
		if (n_must_eat > 0 && philo->eat_count >= n_must_eat)
			exit(255);
		usleep(100);
	}
	return (val);
}

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
	sem_unlink("forks");
	*semaphore = sem_open("forks", O_CREAT, 0644, state->count);
	// int val;
	// sem_getvalue(*semaphore, &val);
	// printf("%d", val);
    if (*semaphore == SEM_FAILED)
	{
		perror("sem_open failed"); 
		exit(EXIT_FAILURE);
	} 
    int i;
    i = -1;
}

void	init(int ac, char* av[], t_state *state, t_philo **philos, sem_t *semaphore) 
{
	int	i;

	check_args(ac, av);
	state->count = ft_atoi(av[1]);
	state->die_time = ft_atoi(av[2]);
	state->eat_time = ft_atoi(av[3]);
	state->sleep_time = ft_atoi(av[4]);
	init_semaphore(&semaphore, state);
	if (ac == 6)
		state->n_must_eat = ft_atoi(av[5]);
	else
		state->n_must_eat = -1;
	state->forks = malloc(sizeof(pthread_mutex_t) * state->count);
	// TODO : VALIDATE ARGS
	i = -1;
	while (++i < state->count)
		pthread_mutex_init(&state->forks[i], NULL);
	*philos = malloc(sizeof(t_philo) * state->count);
	i = -1;
	while (++i < state->count)
	{
		(*philos)[i].state = state;
		(*philos)[i].status = HUNGRY;
		(*philos)[i].l_fork = -1;
		(*philos)[i].r_fork = -1;
		(*philos)[i].index = i;
		(*philos)[i].eat_count = 0;
		(*philos)[i].last_time_eat = get_curr_time((*philos)[i].state);
		(*philos)[i].semaphore = semaphore;
	}
}

void    clear_state(t_state	*state, t_philo *philos, sem_t *semaphore)
{
	int	i;
	int	n;

	i = -1;
	n = state->count;
	while (++i < n)
		pthread_mutex_destroy(&state->forks[i]);
	free(state->forks);
	free(philos);
	sem_close(semaphore);
}
int pids[5];

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
		// philo.semaphore = sem_open("forks", 0);
		if (pthread_create(&threads[0], NULL, &routine, &philo) != 0)
			print_err(COULDNT_CREATE_THREAD);
		if (pthread_create(&threads[1], NULL, &checker,  &philo) != 0)
				print_err(COULDNT_CREATE_THREAD);
		i = -1;
		while (++i < 2)
			if (pthread_join(threads[i], NULL))
				print_err(COULDNT_CREATE_THREAD);
		// printf("I am child process my ID is   =  %d\n" , getpid());
		// philos[i]->pid = getpid();
	}
	static int j;
	pids[j] = pid;
	// printf("I am child process my ID is   =  %d\n" , pid);
	j++;
	return (0);
}

int		init_processes(t_state *state, t_philo *philos)
{
	int	i;
	int wstatus;

	i = -1;
	while (++i < state->count)
		if (spawn_proc(philos[i]) == -1)
			print_err(COULDNT_CREATE_PROCESS);
	while (waitpid(-1, &wstatus, 0) != -1);
	if (WIFEXITED(wstatus))
	{
		int exit_value = WEXITSTATUS(wstatus);
		if (exit_value == 120)
		{
			i = -1;
			while (++i < state->count)
			{
				printf("process killed : %d \n", pids[i]);
				kill(pids[i], SIGKILL);
			}
		}
	}
	return 1;
}
int main(int ac, char* av[])
{
	t_state	state;
	t_philo *philos;
	sem_t *semaphore;

	init(ac, av, &state, &philos, semaphore);
	// init_threads(&state, philos);
	// clear_state(&state, philos, semaphore);
	init_processes(&state, philos);
	return 0;
}