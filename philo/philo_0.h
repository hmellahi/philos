/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_0.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 06:06:08 by hamza             #+#    #+#             */
/*   Updated: 2021/10/01 16:42:38 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_0_H
# define PHILO_0_H
# include "../utils/utils.h"

typedef struct s_state
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

typedef struct s_philo
{
	int		status;
	char	l_fork;
	char	r_fork;
	int		index;
	int		eat_count;
	t_state	*state;
	t_ul	last_time_eat;
}				t_philo;

int		print_msg(int msg_index, t_philo *philo);
int		print_err(int msg_index);
void	init(int ac, char *av[], t_state *state, t_philo **philos);
void	eat(t_philo *philo);
void	take_forks(t_philo *philo, pthread_mutex_t *forks);
void	sleeps(t_philo *philo);
void	throw_forks(t_philo *philo, pthread_mutex_t *forks);
void	think(t_philo *philo);
void	clear_state( t_state *state, t_philo *philos, pthread_t *threads);
#endif