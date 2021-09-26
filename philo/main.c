/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/13 11:40:42 by katherine     #+#    #+#                 */
/*   Updated: 2021/09/26 20:12:25 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	exit_room(t_room *room)
{
	int	i;

	i = 0;
	if (room)
	{
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
	}
}

static void	monitor(t_room *room)
{
	int	i;

	while (!room->philo_died)
	{
		i = 0;
		if (room->satisfied == room->min_times_eat)
			break ;
		while (i < room->num_philo)
		{
			pthread_mutex_lock(&room->monitor);
			if (get_timediff(room->philos[i].last_eaten, get_timestamp()) > \
			room->time_die)
			{
				print_state(dead, &room->philos[i]);
				break ;
			}
			pthread_mutex_unlock(&room->monitor);
			i++;
		}
		smartsleep(50, room->philos);
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
	int		check;

	room = NULL;
	if (argc > 1)
	{
		check = check_input(argc, argv);
		if (check == 1)
			print_error(wrong_args);
		else if (check == 2)
			print_error(invalid_args);
		else
		{
			room = init_room(room, argv);
			if (!start_threads(room))
				print_error(thread_error);
			exit_room(room);
		}
		free(room->print);
		free(room);
	}
	else
		print_error(invalid_args);
	return (0);
}
