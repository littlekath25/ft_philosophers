/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kfu <kfu@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/06 16:23:04 by kfu           #+#    #+#                 */
/*   Updated: 2021/09/10 16:40:34 by kfu           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	smartsleep(int ms, t_philo *philo)
{
	long long	time;
	long long	elapse;

	time = get_timestamp();
	elapse = get_timediff(get_timestamp(), time);
	while (elapse < ms && !philo->room->philo_died)
	{
		usleep(100);
		if (philo->room->philo_died)
			return (0);
		elapse = get_timediff(get_timestamp(), time);
	}
	return (1);
}
