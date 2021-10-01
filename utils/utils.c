/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 19:36:06 by hmellahi          #+#    #+#             */
/*   Updated: 2021/10/01 19:36:14 by hmellahi         ###   ########.fr       */
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
	if (ft_atoi(av[1]) == 0 || ft_atoi(av[1]) > 200)
		return (print_err(NOT_VALID_ARGS));
	return (0);
}

t_ul	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void	ft_usleep(t_ul time)
{
	t_ul	start;

	start = get_time();
	usleep((time - 10) * 1000);
	while ((get_time() - time) < start)
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
