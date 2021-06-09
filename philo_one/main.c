#include "philo_0.h"


int		to_ms(float time, int i)
{
	return (time * 1000);
}

void	*routine(void *val)
{
	t_philo	*philo;
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
	while (philo->state->n_must_eat < 0 || ++j < philo->state->n_must_eat)
	{
		print_msg(PHILO_THINKS, philo);
		pthread_mutex_lock(&forks[i]);
		pthread_mutex_lock(&forks[(i + 1) % n]);
		philo->last_time_eat = get_curr_time(philo->state);
		philo->eat_count++;
		print_msg(PHILO_TAKES_FORK, philo);
		print_msg(PHILO_TAKES_FORK, philo);
		print_msg(PHILO_EATING, philo);
		usleep(to_ms(philo->state->eat_time, 0));
		pthread_mutex_unlock(&forks[i % n]);
		pthread_mutex_unlock(&forks[(i + 1) % n]);
		print_msg(PHILO_SLEEPS, philo);
		usleep(to_ms(philo->state->sleep_time, 0));
	}
	return 0;
}

void	*checker(void *val)
{
	int	i;
	int	n;
	t_philo	*philos;
	int		full;
	int		n_must_eat;

	philos = *(t_philo **)val;
	i = -1;
	n = philos[1].state->count;
	n_must_eat = philos[0].state->n_must_eat;
	while(1)
	{
		full = 0;
		i = -1;
		while (++i < n)
		{
			// printf("%d [[%lu]]\n",philos[i].index, get_curr_time(philos[i].state) - philos[i].last_time_eat);
			if ((get_curr_time(philos[i].state) - philos[i].last_time_eat) >= philos[i].state->die_time)
			{
				print_msg(PHILO_DIES, &philos[i]);
				exit(0);
			}
			if (n_must_eat > 0 && philos[i].eat_count >= n_must_eat)
				full++;
		}
		if (full == n)
			return (val);
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

void	init_state(t_state *state, t_string *av, int ac)
{
	state->count = ft_atoi(av[1]);
	state->die_time = ft_atoi(av[2]);
	state->eat_time = ft_atoi(av[3]);
	state->sleep_time = ft_atoi(av[4]);
	if (ac == 6)
		state->n_must_eat = ft_atoi(av[5]);
	else
		state->n_must_eat = -1;
	state->forks = malloc(sizeof(pthread_mutex_t) * state->count);
}

void	init(int ac, char* av[], t_state *state, t_philo **philos) 
{
	int	i;

	check_args(ac, av);
	init_state(state, av, ac);
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
	}
}

void    clear_state(pthread_t *threads, t_state	*state, t_philo *philos)
{
	int	i;
	int	n;

	i = -1;
	n = state->count;
	while (++i < n)
		pthread_mutex_destroy(&state->forks[i]);
	free(state->forks);
	free(philos);
	free(threads);
}

void	init_threads(pthread_t **threads, t_state *state, t_philo *philos)
{
	int i;
	int	n;

	n = state->count + 1;
	*threads = malloc(sizeof(pthread_t) * n);
	i = -1;
	while (++i < state->count)
		if (pthread_create(&(*threads)[i], NULL, &routine, &philos[i]) != 0)
			print_err(COULDNT_CREATE_THREAD); 
	if (pthread_create(&(*threads)[i], NULL, &checker, &philos) != 0)
		print_err(COULDNT_CREATE_THREAD); 
	i = -1;
	while (++i < n)
		if (pthread_join((*threads)[i], NULL))
			print_err(COULDNT_CREATE_THREAD);
}

unsigned long g_start;

int main(int ac, char* av[])
{
	t_state	state;
	t_philo *philos;
	pthread_t *threads;
	init(ac, av, &state, &philos);
	g_start = 0;
	init_threads(&threads, &state, philos);
	clear_state(threads, &state, philos);
	return 0;
}