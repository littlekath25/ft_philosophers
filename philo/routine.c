/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/30 12:37:13 by katherine     #+#    #+#                 */
/*   Updated: 2021/09/10 16:54:17 by kfu           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	drop_forks(t_philo *philo)
{
	if (pthread_mutex_unlock(philo->left_fork))
		return (0);
	if (pthread_mutex_unlock(philo->right_fork))
		return (0);
	return (1);
}

static int	take_forks(t_philo *philo)
{
	if (philo->room->philo_died)
		return (0);
	if (pthread_mutex_lock(philo->left_fork))
		return (0);
	print_state(taken_fork, philo);
	if (philo->room->philo_died)
		return (0);
	if (pthread_mutex_lock(philo->right_fork))
		return (0);
	if (philo->room->philo_died)
		return (0);
	return (1);
}

static int	start_eating(t_philo *philo)
{
	if (philo->room->philo_died)
		return (0);
	if (!take_forks(philo))
		return (0);
	print_state(taken_fork, philo);
	philo->is_eating = 1;
	print_state(eating, philo);
	smartsleep(philo->room->time_eat, philo);
	philo->last_eaten = get_timestamp();
	philo->is_eating = 0;
	philo->times_eaten++;
	if (!drop_forks(philo))
		return (0);
	return (1);
}

static int	start_sleeping(t_philo *philo)
{
	if (philo->room->philo_died)
		return (0);
	print_state(sleeping, philo);
	if (!smartsleep(philo->room->time_sleep, philo))
		return (0);
	return (1);
}

void	*start_routine(void *ptr)
{
	t_philo			*philo;
	t_room			*room;
	pthread_t		*death;

	room = (t_room *)ptr;
	philo = NULL;
	philo = create_philo(room, philo);
	philo->last_eaten = get_timestamp();
	death = (pthread_t *)ft_calloc(1, sizeof(pthread_t));
	if (philo->position % 2)
		smartsleep(1, philo);
	pthread_create(death, NULL, &check, philo);
	while (!philo->room->philo_died)
	{
		if (!start_eating(philo))
			break ;
		if (!start_sleeping(philo))
			break ;
		if (!philo->room->philo_died)
			print_state(thinking, philo);
		if (room->min_times_eat > 0 && \
		philo->times_eaten == room->min_times_eat)
			break ;
	}
	return (room);
}
