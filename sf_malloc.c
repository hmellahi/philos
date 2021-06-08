enum	status {
	HUNGRY,
	SLEEPING,
	EATING
}

typedef	struct	s_philo
{
	int	eat_time;
	int	die_time;
	int	sleep_time;
	int	n_meals_eaten;
	int	status;
}				t_philo;

typedef	struct	s_state
{
	t_philo	*philos;
	char	*forks;
	int		philos_count;
	float	die_time;
	float	eat_time;
	float	sleep_time;
	float	n_meals_must_eat;
}				t_state;
