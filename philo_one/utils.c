/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 06:04:57 by hamza             #+#    #+#             */
/*   Updated: 2021/06/11 23:56:59 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_0.h"

void	ft_usleep(t_ul time)
{
    t_ul	start;

	start = get_curr_time();
	usleep(time - 20000);
	while ((get_curr_time() - start) < time);
}

int		ft_atoi(const char *str)
{
	int neg;
	int i;
	t_ul num;

	i = 0;
	neg = 1;
	num = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
        if (num > 2147483647)
            return (-1);
		num = num * 10 + (str[i] - 48);
		i++;
	}
	return (num * neg);
}