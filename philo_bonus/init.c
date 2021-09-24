/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/13 17:08:22 by katherine     #+#    #+#                 */
/*   Updated: 2021/09/24 16:17:20 by kfu           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	room = init_philos(room);
	room->start_time = get_timestamp();
	return (room);
}
