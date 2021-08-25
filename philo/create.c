/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/25 15:55:40 by katherine     #+#    #+#                 */
/*   Updated: 2021/08/25 17:28:52 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*test(void *ptr)
{
	return (ptr);
}

void	create_philos(t_room *room)
{
	int	i;
	int	pos;

	room->philos = (t_philo *)ft_calloc(room->num_philo, sizeof(t_philo));
	if (!room->philos)
		error_and_exit(malloc_fail);
	i = 0;
	pos = 1;
	while (i < room->num_philo)
	{
		room->philos[i].position = pos;
		room->philos[i].left_fork = &room->forks[pos - 1];
		if (pos == room->num_philo)
			room->philos[i].right_fork = &room->forks[0];
		else
			room->philos[i].right_fork = &room->forks[pos];
		pos++;
		i++;
	}
	i = 0;
	while (i < room->num_philo)
	{
		printf("PHILO: %i - %i - %i\n", room->philos[i].position, *(room->philos[i]).left_fork, *(room->philos[i]).right_fork);
		i++;
	}
}

void	create_forks(t_room *room)
{
	int	i;

	i = 0;
	room->forks = (int *)ft_calloc(room->num_philo, sizeof(int));
	if (!room->forks)
		error_and_exit(malloc_fail);
	while (i < room->num_philo)
	{
		room->forks[i] = i;
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
		pthread_create(&room->threads[i], NULL, &test, NULL);
		printf("ID: %li - %i\n", room->threads[i], i);
		i++;
	}
}

void	create_room(t_room *room)
{
	create_forks(room);
	create_philos(room);
	create_threads(room);
}
