/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_3.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 02:06:49 by hamza             #+#    #+#             */
/*   Updated: 2021/06/09 18:50:15 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_1_H
# define PHILO_1_H
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <signal.h>

# define ON_TABLE 1
# define USED 0
typedef char*			t_string;
typedef	unsigned long	t_ul;

enum	status {
	HUNGRY,
	SLEEPING,
	EATING
};

enum	messages {
	COULDNT_CREATE_THREAD,
	COULDNT_JOIN_THREAD,
	NOT_VALID_ARGS,
	COULDNT_CREATE_PROCESS,
	PHILO_EATING,
	PHILO_DIES,
	PHILO_SLEEPS,
	PHILO_THINKS,
	PHILO_TAKES_FORK,
};

typedef	struct	s_state
{
	pthread_mutex_t	*forks;
	int				count;
	t_ul			die_time;
	t_ul			eat_time;
	t_ul			sleep_time;
	int				n_must_eat;
	struct timeval	current_time;
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
	sem_t	*semaphore;
}				t_philo;

int				ft_atoi(const char *str);
void			print_msg(int msg_index, t_philo *philo);
void			print_err(int msg_index);
unsigned long   get_curr_time(t_state *state);
#endif