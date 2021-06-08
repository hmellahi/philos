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
	while (++j < philo->state->n_must_eat)
	{
		print_msg(PHILO_THINKS, philo);
		pthread_mutex_lock(&forks[i % n]);
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
			if (philos[i].eat_count == n_must_eat)
				full++;
		}
		if (full == n)
			return (val);
		sleep(1);
	}
	return (val);
}

void	check_args(int ac, t_string	*av)
{
	if (ac != 5 && ac != 6)
	{
		printf("wt are u doing step bruh");
		exit(1);
	}
}

void	init(int ac, char* av[], t_state *state, t_philo **philos) 
{
	int	i;

	check_args(ac, av);
	state->count = ft_atoi(av[1]);
	state->die_time = ft_atoi(av[2]);
	state->eat_time = ft_atoi(av[3]);
	state->sleep_time = ft_atoi(av[4]);
	state->n_must_eat = ft_atoi(av[5]);
	state->forks = sf_malloc(sizeof(pthread_mutex_t) * state->count);
	// TODO : VALIDATE ARGS
	i = -1;
	while (++i < state->count)
		pthread_mutex_init(&state->forks[i], NULL);
	*philos = sf_malloc(sizeof(t_philo) * state->count);
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

void    clear_state(t_state	*state)
{
	int	i;

	i = -1;
	while (++i < state->count)
		pthread_mutex_destroy(&state->forks[i]);
}

void	init_threads(t_state *state, t_philo *philos)
{
	pthread_t *threads;
	int i;
	int	n;

	n = state->count + 1;
	threads = malloc(sizeof(pthread_t) * n);
	i = -1;
	while (++i < state->count)
		if (pthread_create(&threads[i], NULL, &routine, &philos[i]) != 0)
			print_err(COULDNT_CREATE_THREAD); 
	pthread_create(&threads[i], NULL, &checker, &philos);// TODO : PROTECT
	i = -1;
	while (++i < n)
		if (pthread_join(threads[i], NULL))
			print_err(COULDNT_CREATE_THREAD);
}
unsigned long g_start;
int main(int ac, char* av[])
{
	t_state	state;
	t_philo *philos;
	init(ac, av, &state, &philos);
	int i = -1;
	g_start = 0;
	g_start = get_curr_time(&state);
	// while (++i < 5)
	// {
	// 	printf("%d\n", philos[i].eat_count);
	// }
	init_threads(&state, philos);
	clear_state(&state);
	// struct timeval current_time;
	// gettimeofday(&current_time, NULL);
	// printf("seconds : %ld\n", current_time.tv_sec);
	// gettimeofday(&current_time, NULL);
	// printf("seconds : %ld\n", current_time.tv_sec);
	return 0;
}