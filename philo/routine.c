/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/30 12:37:13 by katherine     #+#    #+#                 */
/*   Updated: 2021/09/05 12:59:32 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_eating(t_room *room, t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_state(taken_left_fork, philo, room);
	pthread_mutex_lock(philo->right_fork);
	print_state(taken_right_fork, philo, room);
	philo->is_eating = 1;
	print_state(eating, philo, room);
	usleep(room->time_eat);
	philo->is_eating = 0;
	philo->last_eaten = get_timestamp();
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	start_sleeping(t_room *room, t_philo *philo)
{
	print_state(sleeping, philo, room);
	usleep(room->time_sleep * 1000);
}

void	start_thinking(t_room *room, t_philo *philo)
{
	print_state(thinking, philo, room);
}

int	check_death(t_room *room, t_philo *philo)
{
	long long	time;
	long long	diff;

	time = get_timestamp();
	diff = time - philo->last_eaten;
	if (diff >= room->time_die)
	{
		print_state(dead, philo, room);
		return (0);
	}
	return (1);
}
