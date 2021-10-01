/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 18:37:19 by hmellahi          #+#    #+#             */
/*   Updated: 2021/10/01 18:45:26 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define ON_TABLE 1
# define USED 0
# define DIE_STATUS_CODE 12
typedef char*				t_string;
typedef unsigned long long	t_ul;

enum	e_messages
{
	COULDNT_CREATE_THREAD,
	COULDNT_JOIN_THREAD,
	NOT_VALID_ARGS,
	COULDNT_CREATE_PROCESS,
	PHILO_EATING,
	PHILO_DIES,
	PHILO_SLEEPS,
	PHILO_THINKS,
	PHILO_TAKES_FORK
};

enum	e_status
{
	THINKING,
	SLEEPING,
	EATING
};

int		ft_atoi(const char *str);
void	ft_usleep(t_ul time);
int		check_args(int ac, t_string	*av);
t_ul	get_time(void);
int		print_err(int msg_index);
t_ul	get_time(void);

#endif