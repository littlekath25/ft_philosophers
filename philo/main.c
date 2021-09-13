/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/13 11:40:42 by katherine     #+#    #+#                 */
/*   Updated: 2021/09/13 18:02:53 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	exit_room(t_room *room)
{
	int	i;

	i = 0;
	while (i < room->num_philo)
	{
		pthread_join(room->philos[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < room->num_philo)
	{
		pthread_mutex_destroy(&room->forks[i]);
		i++;
	}
	free(room);
}

static void	monitor(t_room *room)
{
	int	i;

	while (!room->philo_died)
	{
		i = 0;
		while (i < room->num_philo)
		{
			pthread_mutex_lock(&room->monitor);
			if (get_timediff(room->philos[i].last_eaten, get_timestamp()) >= \
			room->time_die)
			{
				print_state(dead, &room->philos[i]);
				room->philo_died = 1;
				break ;
			}
			pthread_mutex_unlock(&room->monitor);
			i++;
		}
		usleep(100);
	}
}

static int	start_threads(t_room *room)
{
	int	i;

	i = 0;
	room->start_time = get_timestamp();
	while (i < room->num_philo)
	{
		if (pthread_create(&room->philos[i].thread, \
		NULL, &start_routine, &room->philos[i]))
			return (0);
		i++;
	}
	monitor(room);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_room	*room;

	room = NULL;
	if (!check_input(argc, argv))
		print_error(invalid_args);
	else
	{
		room = init_room(room, argv);
		if (!start_threads(room))
			print_error(thread_error);
	}
	exit_room(room);
	return (0);
}
