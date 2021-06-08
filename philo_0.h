/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_0.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 06:06:08 by hamza             #+#    #+#             */
/*   Updated: 2021/06/08 03:04:40 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_0_H
# define PHILO_0_H
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>


int		ft_atoi(const char *str);

# define ON_TABLE 1
# define USED 0

enum	status {
	HUNGRY,
	SLEEPING,
	EATING
};

typedef	struct	s_state
{
	pthread_mutex_t	*forks;
	int				count;
	float			die_time;
	float			eat_time;
	float			sleep_time;
	float			n_meals_must_eat;
}				t_state;

typedef	struct	s_philo
{
	int		status;
	char	l_fork;
	char	r_fork;
	int		index;
	t_state	*state;
}				t_philo;

#endif