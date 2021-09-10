/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: kfu <kfu@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/10 16:50:26 by kfu           #+#    #+#                 */
/*   Updated: 2021/09/10 16:51:27 by kfu           ########   odam.nl         */
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

void	*check(void *ptr)
{
	t_philo			*philo;
	long long int	diff;

	philo = (t_philo *)ptr;
	while (!philo->room->philo_died)
	{
		diff = get_timediff(get_timestamp(), philo->last_eaten);
		if (diff > philo->room->time_die && philo-> is_eating != 1)
		{
			print_state(dead, philo);
			philo->room->philo_died = 1;
			break ;
		}
		smartsleep(1, philo);
	}
	return (ptr);
}
