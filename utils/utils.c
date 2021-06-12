/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 06:04:57 by hamza             #+#    #+#             */
/*   Updated: 2021/06/12 19:43:42 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	is_number(t_string str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

int	check_args(int ac, t_string	*av)
{
	int	i;

	if (ac != 5 && ac != 6)
		return (print_err(NOT_VALID_ARGS));
	i = 0;
	while (++i < ac)
		if (!is_number(av[i]) || ft_atoi(av[i]) < 0)
			return (print_err(NOT_VALID_ARGS));
	return (0);
}

void	ft_usleep(t_ul time)
{
	t_ul	start;

	start = get_time();
	usleep(time - 20000);
	while ((get_time() - start) < time)
		;
}

int	ft_atoi(const char *str)
{
	int		neg;
	int		i;
	t_ul	num;

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

t_ul	get_time(void)
{
	t_ul			time_in_ms;
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	time_in_ms = current_time.tv_usec + current_time.tv_sec * 1000000;
	return (time_in_ms);
}
