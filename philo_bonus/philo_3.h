/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_3.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 02:06:49 by hamza             #+#    #+#             */
/*   Updated: 2021/10/01 19:53:28 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_3_H
# define PHILO_3_H
# include "../utils/utils.h"
# include <fcntl.h>
# include <sys/stat.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_state
{
	int				count;
	t_ul			die_time;
	t_ul			eat_time;
	t_ul			sleep_time;
	t_ul			start;
	int				n_must_eat;
	sem_t			*print_sem;
	sem_t			*forks;
	sem_t			*waiter;
}				t_state;

typedef struct s_philo
{
	pid_t	pid;
	int		index;
	int		eat_count;
	t_state	*state;
	t_ul	last_time_eat;
	sem_t	*semaphore;
	char	status;
}				t_philo;

void			print_msg(int msg_index, t_philo *philo);
void			eat(t_philo *philo);
void			take_forks(t_philo *philo);
void			sleeps(t_philo *philo);
void			throw_forks(sem_t *forks);
void			think(t_philo *philo);
void			init(int ac, char *av[], t_state *state, t_philo **philos);
void			*checker(void *val);
void			*routine(void *val);
int				is_number(t_string str);
t_ul			get_time(void);
void			clear_state(t_state	*state, t_philo *philos);
#endif