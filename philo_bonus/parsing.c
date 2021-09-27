/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/13 11:40:08 by katherine     #+#    #+#                 */
/*   Updated: 2021/09/27 11:37:51 by kfu           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_isspace(int c)
{
	if (c == ' ' || c == '\n' || c == '\t' \
	|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	ft_isalldigits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int	res;
	int	sign;
	int	i;

	res = 0;
	sign = 1;
	i = 0;
	while (ft_isspace(str[i]))
	{
		i++;
	}
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] && ft_isdigit(str[i]))
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (sign * res);
}

int	check_input(int argc, char *argv[])
{
	int	i;
	int	num_philo;

	i = 1;
	num_philo = ft_atoi(argv[1]);
	if (argc < 5 || argc > 6)
		return (2);
	else if (num_philo < 2 || num_philo > 200)
		return (1);
	else
	{
		while (argv[i])
		{
			if (!ft_isalldigits(argv[i]))
				return (1);
			i++;
		}
	}
	return (0);
}
