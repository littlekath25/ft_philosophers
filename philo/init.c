/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/13 17:08:22 by katherine     #+#    #+#                 */
/*   Updated: 2021/09/26 19:56:56 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_room	*init_philos(t_room *room)
{
	int	i;

	i = 0;
	while (i < room->num_philo)
	{
		room->philos[i].position = i + 1;
		room->philos[i].is_eating = 0;
		room->philos[i].times_eaten = 0;
		room->philos[i].left_fork = i;
		room->philos[i].right_fork = i + 1;
		if (room->philos[i].right_fork == room->num_philo)
			room->philos[i].right_fork = 0;
		room->philos[i].last_eaten = get_timestamp();
		room->philos[i].room = room;
		i++;
	}
	return (room);
}

static t_room	*init_forks_and_print(t_room *room)
{
	int	i;

	i = 0;
	while (i < room->num_philo)
	{
		if (pthread_mutex_init(&room->forks[i], NULL))
		{
			print_error(mutex_error);
			return (NULL);
		}
		i++;
	}
	room->print = ft_calloc(sizeof(pthread_t), 1);
	if (pthread_mutex_init(&(*room->print), NULL))
	{
		print_error(mutex_error);
		return (NULL);
	}
	return (room);
}

static t_room	*init_philos_and_forks(t_room *room)
{
	room = init_forks_and_print(room);
	room = init_philos(room);
	return (room);
}

t_room	*init_room(t_room *room, char *argv[])
{
	room = (t_room *)malloc(sizeof(t_room) * 1);
	room->num_philo = ft_atoi(argv[1]);
	if (room->num_philo > 200 || room->num_philo < 2)
	{
		print_error(wrong_args);
		return (NULL);
	}
	room->time_die = ft_atoi(argv[2]);
	room->time_eat = ft_atoi(argv[3]);
	room->time_sleep = ft_atoi(argv[4]);
	if (argv[5])
		room->min_times_eat = ft_atoi(argv[5]);
	else
		room->min_times_eat = -1;
	if (room->num_philo < 2 || room->min_times_eat == 0)
	{
		print_error(wrong_args);
		return (NULL);
	}
	room->philo_died = 0;
	room->satisfied = 0;
	room = init_philos_and_forks(room);
	return (room);
}
