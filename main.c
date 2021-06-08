#include "philo_0.h"

void	*routine(t_philo *philo)
{
	pthread_mutex_t *forks;
	int				i;
	int				n;

	forks = philo->state->forks;
	i = philo->index;
	n = philo->state->count;
	pthread_mutex_lock(&forks[i % n]);
	pthread_mutex_lock(&forks[(i + 1) % n]);
	printf("%d Eating\n", i + 1);
	sleep(philo->state->eat_time / 1000);
	pthread_mutex_unlock(&forks[i % n]);
	pthread_mutex_unlock(&forks[(i + 1) % n]);
	printf("%d Sleeping\n", i + 1);
	sleep(philo->state->sleep_time / 1000);
}

void	check(t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < philos->state->count)
	{
		if (philos[i]->state->time_to_die == 0)
		{
			printf("philo %d died", i + 1);
			exit(0);
		}
	}
}

void	*sf_malloc(int size)
{
	return malloc(size);
}


void	init(int ac, char* av[], t_state *state, t_philo *philos) 
{
	int	i;

	if (ac != 5 && ac != 6)
	{
		printf("wt are u doing step bruh");
		exit(1);
	}
	state->die_time = ft_atoi(av[2]);
	state->eat_time = ft_atoi(av[3]);
	state->sleep_time = ft_atoi(av[4]);
	state->n_meals_must_eat = ft_atoi(av[5]);
	state->count = av[1];
	state->forks = sf_malloc(sizeof(pthread_mutex_t) * state->count);
	// TODO : VALIDATE ARGS
	i = -1;
	while (++i < state->count)
		pthread_mutex_init(&state->forks[i], NULL);
	philos = sf_malloc(sizeof(t_philo) * state->count);
	while (++i < state->count)
	{
		philos[i].state = state;
		philos[i].status = HUNGRY;
		philos[i].l_fork = -1;
		philos[i].r_fork = -1;
		philos[i].index = i;
	}
}

void    clear_state(t_state	*state)
{
	int	i;

	i = -1;
	while (++i < state->count)
		pthread_mutex_destroy(&state->forks[i]);
}

void	checker()
{

}

void	init_threads(t_state *state, t_philo *philos)
{
	pthread_t *threads;
	int i;
	int	n;

	n = state->count;
	threads = malloc(sizeof(pthread_t) * n);
	i = -1;
	while (++i < state->count)
	{
		pthread_create(&threads[i], NULL, &routine, &philos[i]); // TODO : PROTECT
	}
	// pthread_create(&threads[i], NULL, &checker, &philos[i]);// TODO : PROTECT
	i = -1;
	while (++i < n)
	{
		pthread_join(threads[i], NULL); // TODO : PROTECT
	}
}
int main(int ac, char* av[])
{
	t_state	state;
	t_philo *philos;
	init(ac, av, &state, &philos);
	init_threads(&state, &philos);
	clear_state(&state);
	return 0;
}
// int main(void)
// {
//     int i;
//     struct timeval temps_avant, temps_apres;
 
//     gettimeofday (&temps_avant, NULL);
 
//     // for(i=0; i<2000000000; i++);
 
//     gettimeofday (&temps_apres, NULL);
 
//     printf("temps en us: %ld us\n", ((temps_apres.tv_sec - temps_avant.tv_sec) * 1000000 + temps_apres.tv_usec) - temps_avant.tv_usec);
 
// }