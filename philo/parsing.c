/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/15 19:52:52 by katherine     #+#    #+#                 */
/*   Updated: 2021/08/15 19:53:35 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\n' || c == '\t' \
	|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
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

int	ft_isalldigits(char *str)
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

int	check_input(int argc, char *argv[])
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
		return (0);
	else
	{
		while (argv[i])
		{
			if (ft_isalldigits(argv[i]) == 0)
				error_and_exit(wrong_args);
			i++;
		}
	}
	return (1);
}
