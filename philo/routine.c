/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/30 12:37:13 by katherine     #+#    #+#                 */
/*   Updated: 2021/08/30 18:14:02 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_eating(t_room *room, t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	printf("PHILO %i PICKED UP A LEFT FORK\n", philo->position);
	pthread_mutex_lock(philo->right_fork);
	printf("PHILO %i PICKED UP A RIGHT FORK\n", philo->position);
	if ((philo->left_fork->__data.__lock == 1) && (philo->right_fork->__data.__lock == 1))
	{
		philo->is_eating = 1;
		printf("PHILO %i STARTED EATING\n", philo->position);
		usleep(room->time_eat);
		philo->is_eating = 0;
	}
	philo->last_eaten = get_timestamp();
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	start_sleeping(t_room *room, t_philo *philo)
{
	printf("PHILO %i STARTED SLEEPING\n", philo->position);
	usleep(room->time_eat);
}

void	start_thinking(t_room *room, t_philo *philo)
{
	printf("PHILO %i STARTED THINKING\n", philo->position);
}

int	check_death(t_room *room, t_philo *philo)
{
	long long	time;
	long long	diff;

	time = get_timestamp();
	diff = time - philo->last_eaten;
	if (diff >= room->time_die)
	{
		printf("PHILO %i HAS DIED\n", philo->position);
		return (0);
	}
	return (1);
}
