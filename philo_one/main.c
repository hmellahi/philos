#include "philo_0.h"


void	ft_usleep(t_ul time)
{
    t_ul	start;

	start = get_curr_time();
	usleep(time - 20000);
	while ((get_curr_time() - start) < time);
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
		philo->status = THINKING;
		pthread_mutex_lock(&forks[i]);
		philo->status = EATING;
		print_msg(PHILO_TAKES_FORK, philo);
		pthread_mutex_lock(&forks[(i + 1) % n]);
		print_msg(PHILO_TAKES_FORK, philo);
		philo->last_time_eat = get_curr_time();
		// printf("[[%d]\n", philo->status);
		print_msg(PHILO_EATING, philo);
		ft_usleep(philo->state->eat_time);
		philo->eat_count++;
		pthread_mutex_unlock(&forks[i]);
		pthread_mutex_unlock(&forks[(i + 1) % n]);
		// philo->l_fork = -1;
		// philo->r_fork = -1;
		philo->status = SLEEPING;
		print_msg(PHILO_SLEEPS, philo);
		ft_usleep(philo->state->sleep_time);
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
			if (philos[i].status != 2 && (get_curr_time(philos[i].state) - philos[i].last_time_eat) >= philos[i].state->die_time)
			{
				// printf("[%d]\n", philos[i].status);
				print_msg(PHILO_DIES, &philos[i]);
				exit(0);
			}
			if (n_must_eat > 0 && philos[i].eat_count == n_must_eat)
				full++;
		}
		if (full == n)
			return (val);
		usleep(10);
	}
	return (val);
}

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
// CHANGE
void	check_args(int ac, t_string	*av)
{
	int	i;

	if (ac != 5 && ac != 6)
		print_err(NOT_VALID_ARGS);
	i = 0;
	while (++i < ac)
		if (!is_number(av[i]) || ft_atoi(av[i]) < 0)
			print_err(NOT_VALID_ARGS);
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

	check_args(ac, av);
	init_state(state, av, ac);
	i = -1;
	pthread_mutex_init(&state->print_mutex, NULL);
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

void    clear_state( t_state	*state, t_philo *philos)
{
	int	i;
	int	n;

	i = -1;
	n = state->count;
	pthread_mutex_destroy(&state->print_mutex);
	while (++i < n)
		pthread_mutex_destroy(&state->forks[i]);
	free(state->forks);
	free(philos);
}

void	init_threads(t_state *state, t_philo *philos)
{
	int i;
	int	n;
	pthread_t	threads[state->count + 1];

	n = state->count + 1;
	i = -1;
	while (++i < state->count)
	{
		if (pthread_create(&threads[i], NULL, &routine, &philos[i]) != 0)
			print_err(COULDNT_CREATE_THREAD); 
		usleep(100);
	}
	if (pthread_create(&threads[i], NULL, &checker, &philos) != 0)
		print_err(COULDNT_CREATE_THREAD);
	i = -1;
	while (++i < n)
		if (pthread_join(threads[i], NULL))
			print_err(COULDNT_CREATE_THREAD);
}

unsigned long g_start;

int main(int ac, char* av[])
{
	t_state	state;
	t_philo	*philos;

	state.start_time = get_curr_time();
	init(ac, av, &state, &philos);
	g_start = 0;
	init_threads(&state, philos);
	clear_state(&state, philos);
	return 0;
}