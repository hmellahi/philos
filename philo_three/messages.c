/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 16:23:49 by hmellahi          #+#    #+#             */
/*   Updated: 2021/06/11 00:11:26 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_3.h"

void    print_err(int msg_index)
{
    t_string    *messages;

    messages[0] = "couldnt create a thread";
    messages[1] = "couldnt join a thread";
    messages[1] = "not valid args";
    messages[3] = "COULDNT_CREATE_PROCESS";
    printf("%s\n", messages[msg_index]);
    // clear_state();
    exit(1);
}

extern unsigned long g_start;
unsigned long   get_curr_time()
{
    unsigned long time_in_ms;
    struct timeval current_time;

    gettimeofday(&current_time, NULL);
    time_in_ms = current_time.tv_usec + current_time.tv_sec * 1000000;
    return (time_in_ms);
}

void    print_msg(int msg_index, t_philo *philo)
{
    unsigned long time_in_ms;

    time_in_ms = get_curr_time();
    sem_wait(philo->state->print_sem);
    if (msg_index == PHILO_TAKES_FORK)
        printf("%lu %d has taken a fork\n", time_in_ms, philo->index + 1);
    else if (msg_index == PHILO_EATING)
        printf("%lu %d is eating\n", time_in_ms, philo->index + 1);
    else if (msg_index == PHILO_DIES)
    {
        printf("%lu %d died\n", time_in_ms, philo->index + 1);
        exit(DIE_STATUS_CODE);
    }
    else if (msg_index == PHILO_THINKS)
        printf("%lu %d is thinking\n", time_in_ms, philo->index + 1);
    else if (msg_index == PHILO_SLEEPS)
        printf("%lu %d is sleeping\n", time_in_ms, philo->index + 1);
    sem_post(philo->state->print_sem);
}