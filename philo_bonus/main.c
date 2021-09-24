/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kfu <kfu@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/17 13:46:41 by kfu           #+#    #+#                 */
/*   Updated: 2021/09/24 16:44:03 by kfu           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	kill_all(t_room *room)
{
	int	i;

	i = 0;
	while (i < room->num_philo)
	{
		kill(room->philos[i].id, 0);
		i++;
	}
}

static void	monitor(t_room *room)
{
	int		i;
	pid_t	id;

	while (!room->philo_died)
	{
		i = 0;
		if (room->satisfied == room->min_times_eat)
			break ;
		while (i < room->num_philo)
		{
			if (get_timediff(room->philos[i].last_eaten, get_timestamp()) > \
			room->time_die)
			{
				print_state(dead, &room->philos[i]);
				room->philo_died = 1;
				kill_all(room);
				break ;
			}
			i++;
		}
		smartsleep(100, room->philos);
	}
}

static void	fork_philos(t_room *room)
{
	int		i;
	pid_t	id;

	i = 0;
	while (i < room->num_philo && id != 0)
	{
		id = fork();
		if (id == 0)
			start_routine(&room->philos[i]);
		i++;
	}
	if (id != 0)
	{
		id = fork();
		if (id == 0)
			monitor(room);
	}
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
			fork_philos(room);
		}
		free(room);
	}
	else
		print_error(invalid_args);
	return (0);
}
