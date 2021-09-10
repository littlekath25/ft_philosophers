/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/30 12:37:13 by katherine     #+#    #+#                 */
/*   Updated: 2021/09/10 14:49:36 by kfu           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check(void *ptr)
{
	t_philo			*philo;
	long long int	diff;

	philo = (t_philo *)ptr;
	while (1)
	{
		diff = get_timediff(get_timestamp(), philo->last_eaten);
		if (diff > philo->room->time_die && philo-> is_eating != 1)
		{
			print_state(dead, philo);
			exit(0);
		}
		smartsleep(1);
	}
	return (ptr);
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
		smartsleep(1);
	pthread_create(death, NULL, &check, philo);
	while (1)
	{
		start_eating(philo);
		start_sleeping(philo);
		print_state(thinking, philo);
		if (room->min_times_eat > 0 && \
		philo->times_eaten == room->min_times_eat)
			break ;
	}
	return (room);
}

void	start_eating(t_philo *philo)
{
	if (pthread_mutex_lock(philo->left_fork))
		return ;
	print_state(taken_fork, philo);
	if (pthread_mutex_lock(philo->right_fork))
		return ;
	print_state(taken_fork, philo);
	philo->is_eating = 1;
	print_state(eating, philo);
	smartsleep(philo->room->time_eat);
	philo->last_eaten = get_timestamp();
	philo->is_eating = 0;
	philo->times_eaten++;
	if (pthread_mutex_unlock(philo->left_fork))
		return ;
	if (pthread_mutex_unlock(philo->right_fork))
		return ;
}

void	start_sleeping(t_philo *philo)
{
	print_state(sleeping, philo);
	smartsleep(philo->room->time_sleep);
}
