/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/25 15:55:40 by katherine     #+#    #+#                 */
/*   Updated: 2021/09/06 17:01:40 by kfu           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*create_philo(t_room *room, t_philo *philo)
{
	philo = (t_philo *)ft_calloc(1, sizeof(t_philo));
	if (!philo)
		error_and_exit(malloc_fail);
	philo->position = room->position;
	philo->left_fork = &room->forks[room->position - 1];
	if (room->position == room->num_philo)
		philo->right_fork = &room->forks[0];
	else
		philo->right_fork = &room->forks[room->position];
	philo->room = room;
	room->position++;
	return (philo);
}

void	create_forks(t_room *room)
{
	int	i;

	i = 0;
	room->forks = \
	(pthread_mutex_t *)ft_calloc(room->num_philo, sizeof(pthread_mutex_t));
	if (!room->forks)
		error_and_exit(malloc_fail);
	while (i < room->num_philo)
	{
		if (pthread_mutex_init(&room->forks[i], NULL))
			error_and_exit(mutex_error);
		i++;
	}
}

void	create_threads(t_room *room)
{
	int	i;

	i = 0;
	room->threads = (pthread_t *)ft_calloc(room->num_philo, sizeof(pthread_t));
	if (!room->threads)
		error_and_exit(malloc_fail);
	while (i < room->num_philo)
	{
		pthread_create(&room->threads[i], NULL, &start_routine, room);
		i++;
	}
	i = 0;
	while (i < room->num_philo)
	{
		pthread_join(room->threads[i], NULL);
		i++;
	}
}

void	create_room(t_room *room)
{
	create_forks(room);
	create_threads(room);
}
