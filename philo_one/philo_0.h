/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_0.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 06:06:08 by hamza             #+#    #+#             */
/*   Updated: 2021/06/12 00:42:36 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_0_H
# define PHILO_0_H
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>
#include <unistd.h>

# define ON_TABLE 1
# define USED 0
typedef char*			t_string;
typedef	unsigned long	t_ul;

enum	status {
	THINKING,
	SLEEPING,
	EATING
};

enum	messages {
	COULDNT_CREATE_THREAD,
	COULDNT_JOIN_THREAD,
	NOT_VALID_ARGS,
	PHILO_EATING,
	PHILO_DIES,
	PHILO_SLEEPS,
	PHILO_THINKS,
	PHILO_TAKES_FORK
};

typedef	struct	s_state
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	waiter;
	int				count;
	t_ul			die_time;
	t_ul			eat_time;
	t_ul			sleep_time;
	int				n_must_eat;
	struct timeval	current_time;
	t_ul			start_time;
}				t_state;

typedef	struct	s_philo
{
	int		status;
	char	l_fork;
	char	r_fork;
	int		index;
	int		eat_count;
	t_state	*state;
	t_ul	last_time_eat;
}				t_philo;

int		ft_atoi(const char *str);
void	*sf_malloc(int size);
void    print_msg(int msg_index, t_philo *philo);
int		print_err(int msg_index);
unsigned long   get_curr_time();
void	init(int ac, char* av[], t_state *state, t_philo **philos);
void	ft_usleep(t_ul time);
void	eat(t_philo *philo);
void	take_forks(t_philo *philo, pthread_mutex_t *forks);
void	sleeps(t_philo *philo);
void	throw_forks(t_philo *philo, pthread_mutex_t *forks);
void	think(t_philo *philo);
int		check_args(int ac, t_string	*av);
void    clear_state( t_state	*state, t_philo *philos);
void	*die_and_exit(t_philo *philo, void *val);
#endif